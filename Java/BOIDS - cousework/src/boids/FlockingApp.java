package boids;

import java.lang.System;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.awt.Color;
import java.awt.geom.AffineTransform;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.util.ArrayList;
import java.util.Hashtable;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

public class FlockingApp {
    public static Dimension sSize;
    public static int hor;
    public static int vert;
    public static int numBoids = 15;
    public static JLabel label;
    public static JSlider slider;
    public FlockingApp() {
        sSize = Toolkit.getDefaultToolkit().getScreenSize();
        hor = sSize.width;;
        vert = sSize.height;
        //numBoids = 15;
    }
    private static void createAndShowUI() {
        JFrame frame = new JFrame("Boids");
        label = new JLabel();
        label.setText("Number of boids: " + numBoids);
        label.setFont(new Font("Times New Roman", Font.PLAIN, 35));
        label.setVerticalAlignment(JLabel.CENTER);

        slider = new JSlider(JSlider.HORIZONTAL, 0, 50, 15);
        slider.setPaintLabels(true);
        slider.setPaintTicks(true);
        slider.setMinorTickSpacing(1);
        slider.setMajorTickSpacing(5);
        slider.setOpaque(false);
        slider.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent event) {
                numBoids = slider.getValue();
                label.setText("Number of boids: " + numBoids);
            }
        });

        FlockingPanel panel = new FlockingPanel();
        panel.setLayout(new BorderLayout());
        frame.getContentPane().add(panel);
        panel.add(slider, BorderLayout.NORTH);
        panel.add(label, BorderLayout.PAGE_END);

        frame.getContentPane().setPreferredSize(new Dimension(FlockingApp.hor, FlockingApp.vert));
        //frame.getContentPane().setSize(FlockingApp.hor, FlockingApp.vert);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }
    public static void main(String[] args) {
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                createAndShowUI();
            }
        });
    }
}

@SuppressWarnings("serial")
class FlockingPanel extends JPanel {
    private static final int TIMER_DELAY = 10;
    private int numBoids = FlockingApp.numBoids;
    private ArrayList<Boid> boids = new ArrayList<>(numBoids);
    private ArrayList<LeaderBoid> leaders = new ArrayList<>(1);
    Hashtable<String, Behaviour> behaviours = new Hashtable<>();
    private int align_radius = 50;
    private int cohes_radius = 50;
    private int separ_radius = 50;
    private double align_weight = 0.802;
    private double cohes_weight = 0.01;
    private double separ_weight = 0.6;//0.6;
    private double align_angle = Math.PI / 2;
    private double cohes_angle = Math.PI / 2;// / 1.5;
    private double separ_angle = Math.PI;
    public FlockingPanel() {
        super();
        setBackground(Color.white);
        behaviours.put("Seek", new Seek(200, Math.PI / 3, 1.0));
        behaviours.put("Alignment", new Alignment(align_radius, align_angle, align_weight));
        behaviours.put("Cohesion", new Cohesion(cohes_radius, cohes_angle, cohes_weight));
        behaviours.put("Separation", new Separation(separ_radius, separ_angle, separ_weight));
        //behaviours.put("Jitter", new Jitter(0, 0.0, 0.0025, 2.0, 2.0));
        behaviours.put("AvoidPoint1", new AvoidPoint(60, Math.PI / 3, 0.5));
        behaviours.put("AvoidPoint2", new AvoidPoint(30, Math.PI / 3, 0.5));
        behaviours.put("AvoidPoint3", new AvoidPoint(40, Math.PI / 3, 0.5));
        //behaviours.put("AvoidPoint4", new AvoidPoint(50, Math.PI / 3, 0.5));

        TouchListener tl = new TouchListener();
        addMouseListener(tl);
        addMouseMotionListener(tl);
        setKeyBindings();

        //for (int i = 0; i < 1; ++i) {
        leaders.add(new LeaderBoid());
        //}

        for (int i = 0; i < numBoids; ++i) {
            boids.add(new Boid());
            boids.get(i).setNumber(i);
        }

        javax.swing.Timer timer = new javax.swing.Timer(TIMER_DELAY,
                new ActionListener() {
                    public void actionPerformed(ActionEvent arg0) {
                        FlockingPanel.this.repaint();
                    }
                });
        timer.start();
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2 = (Graphics2D) g;
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
                RenderingHints.VALUE_ANTIALIAS_ON);
        //((AvoidPoint) behaviours.get("AvoidPoint")).setActive(true);
        AvoidPoint avoidPoint1 = (AvoidPoint) behaviours.get("AvoidPoint1");
        AvoidPoint avoidPoint2 = (AvoidPoint) behaviours.get("AvoidPoint2");
        AvoidPoint avoidPoint3 = (AvoidPoint) behaviours.get("AvoidPoint3");
        AvoidPoint tunnel = (AvoidPoint) behaviours.get("AvoidPoint4");
        //behaviours.get("Cohesion").invert(avoidPoint.isActive());
        //CIRCLE AROUND AVOIDING AREA
        double r = avoidPoint1.radius();
        int d = (int) (2 * r);

        avoidPoint1.updatePoint(600, 570);
        Vec2 point1 = avoidPoint1.point();
        avoidPoint1.setShape("Oval");
        g2.setColor(Color.red);
        g2.drawOval((int) (point1.x() - 3), (int) (point1.y() - 3), 6, 6);
        g2.setColor(Color.red.darker());
        g2.drawOval((int) (point1.x() - r), (int) (point1.y() - r), d, d);

        r = avoidPoint2.radius();
        d = (int) (2 * r);
        avoidPoint2.updatePoint(250, 350);
        avoidPoint2.setShape("Triangle");
        Vec2 point2 = avoidPoint2.point();
        g2.setColor(Color.red);
        g2.drawOval((int) (point2.x() - 3), (int) (point2.y() - 3), 6, 6);
        //1-я точка в массиве - вершина треугольника снизу;
        //2-я точка - левая вершина;
        //3-я - правая;
        //2*r - радиус описанной окружности
        //Math.sqrt(3) * r - половина стороны треуголька
        //r - радиус вписанной окружности
        int [] xpoints = {(int) (point2.x()), (int) (point2.x() - Math.sqrt(3) * r), (int) (point2.x() + Math.sqrt(3) * r)};
        int [] ypoints = {(int) (point2.y() + 2 * r), (int) (point2.y() - r), (int) (point2.y() - r)};
        g2.setColor(Color.red.darker());
        g2.drawPolygon(xpoints, ypoints, 3);

        r = avoidPoint3.radius();
        d = (int) (2 * r);
        avoidPoint3.updatePoint(670, 300);
        avoidPoint3.setShape("Square");
        Vec2 point3 = avoidPoint3.point();
        g2.setColor(Color.red);
        g2.drawOval((int) (point3.x() - 3), (int) (point3.y() - 3), 6, 6);
        g2.setColor(Color.red.darker());
        g2.drawRect((int) (point3.x() - r), (int) (point3.y() - r), d, d);

        /*tunnel.updatePoint(950, 450);
        avoidPoint3.setShape("tunnel");*/

        /*g2.setColor(Color.red);
        g2.drawLine(800, 400, 1100, 400);
        g2.drawLine(800, 500, 1100, 500);*/

        Seek seek_behaviour = (Seek) behaviours.get("Seek");
        //CIRCLE AROUND TENDING AREA
        if (seek_behaviour.isActive()) {
            Vec2 point_seek = seek_behaviour.point();
            double r_seek = seek_behaviour.radius();
            int d_seek = (int) (2 * r_seek);
            g2.setColor(Color.red);
            g2.drawOval((int) (point_seek.x() - 3), (int) (point_seek.y() - 3), 6, 6);
            g2.setColor(Color.cyan.darker());
            g2.drawOval((int) (point_seek.x() - r_seek), (int) (point_seek.y() - r_seek), d_seek, d_seek);
            g2.setColor(Color.blue.brighter());
            g2.drawOval((int) (point_seek.x() - 50 ), (int) (point_seek.y() - 3 * r_seek/4 - 50), 100, 100);
            g2.setColor(Color.blue.brighter());
            g2.drawOval((int) (point_seek.x() - 50 ), (int) (point_seek.y() + 3 * r_seek/4 - 50), 100, 100);
            g2.setColor(Color.blue.brighter());
            g2.drawOval((int) (point_seek.x() + 3 * r_seek/4 - 50 ), (int) (point_seek.y() - 50), 100, 100);

            for (int i = 0; i < boids.size(); ++i) {
                double radius = 3 * r_seek / 4;
                if (((boids.get(i).pos().x() - point_seek.x()) * (boids.get(i).pos().x() - point_seek.x())
                        + (boids.get(i).pos().y() - (point_seek.y() - radius)) * (boids.get(i).pos().y()
                        - (point_seek.y() - radius)) < radius * radius / 16)) {

                    boids.remove(boids.get(i));

                    numBoids = boids.size();
                    FlockingApp.label.setText("Number of boids: " + numBoids);
                    FlockingApp.numBoids = boids.size();
                    FlockingApp.slider.setValue(numBoids);
                }

                if (((boids.get(i).pos().x() - point_seek.x()) * (boids.get(i).pos().x() - point_seek.x())
                        + (boids.get(i).pos().y() - (point_seek.y() + radius)) * (boids.get(i).pos().y()
                        - (point_seek.y() + radius)) < radius * radius / 16)) {

                    boids.remove(boids.get(i));

                    numBoids = boids.size();
                    FlockingApp.label.setText("Number of boids: " + numBoids);
                    FlockingApp.numBoids = boids.size();
                    FlockingApp.slider.setValue(numBoids);
                }

                if (((boids.get(i).pos().x() - (point_seek.x() + radius)) * (boids.get(i).pos().x()
                        - (point_seek.x() + radius)) + (boids.get(i).pos().y() - point_seek.y())
                        * (boids.get(i).pos().y() - point_seek.y()) < radius * radius / 16)) {

                    boids.remove(boids.get(i));

                    FlockingApp.label.setText("Number of boids: " + boids.size());
                    FlockingApp.numBoids = boids.size();
                    FlockingApp.slider.setValue(boids.size());
                }
            }

            for (int i = 0; i < boids.size(); ++i) {
                boids.get(i).setNumber(i);
            }
        }


        numBoids = FlockingApp.numBoids;
        int differ = numBoids - boids.size();
        if (differ > 0) {
            for (int i = 0; i < differ; ++i) {
                boids.add(new Boid());
                //boids.get(i + boids.size() - 2).setNumber(i + boids.size() - 2);
            }
            for (int i = 0; i < boids.size(); ++i) {
                boids.get(i).setNumber(i);
            }
        } else {
            for (int i = 0; i < -differ; ++i) {
                boids.remove(i);
            }
            for (int i = 0; i < boids.size(); ++i) {
                boids.get(i).setNumber(i);
            }
        }

        for (LeaderBoid leader : leaders) {
            for (Behaviour b : behaviours.values()) {
                b.applyLeader(leaders, leader);
            }
        }

        for (LeaderBoid leader : leaders) {
            leader.setColor(Color.black);
            leader.attractFollower(boids);
            leader.beginCommunication();
            leader.update();
            leader.boundPosition(25, 25, FlockingApp.hor - 25, FlockingApp.vert - 50);
            leader.draw(g2);
            leader.acc(0.0, 0.0);
            //System.out.println(leader.getLeaderPosition());
        }
        for (Boid boid : boids) {
            for (Behaviour b : behaviours.values()) {
                b.apply(boids, boid);
            }
            boid.setNumberOfBoids(numBoids);
        }
        for (Boid boid : boids) {
            boid.update();
            boid.boundPosition(25, 25, FlockingApp.hor - 25, FlockingApp.vert - 50);
            boid.draw(g2);
            boid.acc(0.0, 0.0);
        }
    }
    private class TouchListener implements MouseListener, MouseMotionListener {
        private boolean mouseDown = false;
        @Override
        public void mouseDragged(MouseEvent event) {
            ((Seek) behaviours.get("Seek")).updatePoint(event.getPoint().x, event.getPoint().y);
        }
        @Override
        public void mouseMoved(MouseEvent event) {
            /*((AvoidPoint) behaviours.get("AvoidPoint")).updatePoint(event.getPoint().x, event.getPoint().y);
            ((AvoidPoint) behaviours.get("AvoidPoint")).setActive(true);
            mouseDown = true;*/
        }
        @Override
        public void mouseClicked(MouseEvent event) {
            ((Seek) behaviours.get("Seek")).updatePoint(event.getPoint().x, event.getPoint().y);
            ((Seek) behaviours.get("Seek")).setActive(true);
            mouseDown = true;
        }
        @Override
        public void mouseEntered(MouseEvent event) {
            ((Seek) behaviours.get("Seek")).setActive(mouseDown);
        }
        @Override
        public void mouseExited(MouseEvent event) {
            /*((Seek) behaviours.get("Seek")).setActive(false);*/
        }
        @Override
        public void mousePressed(MouseEvent event) {
        }
        @Override
        public void mouseReleased(MouseEvent event) {
            /*((Seek) behaviours.get("Seek")).setActive(false);
            mouseDown = false;*/
        }
    }
    private void setKeyBindings() {
        ActionMap actionMap = getActionMap();
        int condition = JComponent.WHEN_IN_FOCUSED_WINDOW;
        InputMap inputMap = getInputMap(condition);
        String vkLeft = "VK_LEFT";
        String vkRight = "VK_RIGHT";
        inputMap.put(KeyStroke.getKeyStroke(KeyEvent.VK_LEFT, 0), vkLeft);
        inputMap.put(KeyStroke.getKeyStroke(KeyEvent.VK_RIGHT, 0), vkRight);
        actionMap.put(vkLeft, new KeyAction(vkLeft));
        actionMap.put(vkRight, new KeyAction(vkRight));
    }
    private class KeyAction extends AbstractAction {
        public KeyAction(String actionCommand) {
            putValue(ACTION_COMMAND_KEY, actionCommand);
        }
        @Override
        public void actionPerformed(ActionEvent actionEvt) {
            System.out.println(actionEvt.getActionCommand() + " pressed");
            if ("VK_RIGHT".equals(actionEvt.getActionCommand())) {
                boids.add(new Boid());
            }
        }
    }
}