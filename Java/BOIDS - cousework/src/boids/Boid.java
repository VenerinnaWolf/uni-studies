package boids;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Polygon;
import java.util.Hashtable;
import java.util.List;
public class Boid {
    private Vec2 position, velocity, acceleration;
    private Color boidColour = Color.magenta.darker();
    private static final double velLimit = 1.0 * 2;
    private  int number, num_boids;
    private static final double accLimit = 0.02 * 2;
    private Vec2 leaderPosition, leaderVelocity;
    private LeaderBoid leader;
    private boolean hasLeader = false;
    FlockingApp sizes = new FlockingApp();
    public Boid() {
        position = new Vec2(Math.random() * 50, Math.random() * (FlockingApp.vert - 600));
        //position = new Vec2(FlockingApp.hor / 2, FlockingApp.vert / 2);
        double vx = Math.random();
        double vy = Math.random();
        velocity = new Vec2(vx, vy);
        acceleration = new Vec2();
        num_boids = 15;
    }
    public Vec2 pos() {
        return position;
    }
    public Vec2 vel() {
        return velocity;
    }
    public void acc(double x, double y) {
        acceleration = new Vec2(x, y);
    }
    public void update() {
        double length = acceleration.magnitude();
        if (length > accLimit) {
            acceleration = acceleration.scale(1 / (length / accLimit));
        }
        velocity = velocity.plus(acceleration);
        length = velocity.magnitude();
        if (length > velLimit) {
            velocity = velocity.scale(1 / (length / velLimit));
        }
        //velocity = velocity.plus(acceleration);

        position = position.plus(velocity);
    }
    public void applyForce(Vec2 force) {
        if (force != null) {
            acceleration = acceleration.plus(force); // Assume a mass of one unit
        }
    }
    public void boundPosition(int xMin, int yMin, int xMax, int yMax) {
        double x = position.x(), y = position.y();
        double vx = velocity.x(), vy = velocity.y();

        /*if (x < xMin) {
            x = xMin;
        } else if (x > xMax) {
            x = xMax;
        }
        if (y < yMin) {
            y = yMin;
        } else if (y > yMax) {
            y = yMax;
        }*/

        final int turnFactor = 15;

        if (x < xMin) {
            vx += turnFactor;
        }
        if (x > xMax) {
            vx -= turnFactor;
        }
        if (y < yMin) {
            vy += turnFactor;
        }
        if (y > yMax) {
            vy -= turnFactor;
        }

        /*if ((y < 400 / 3 + x / 3) && (x < 3*y - 400)) {
            vx += turnFactor;
            vy += turnFactor;
        }
        if ((y > 400 / 3 + x / 3) && (x > 3*y - 400)) {
            vx -= turnFactor;
            vy -= turnFactor;
        }
        if ((y < 700 / 3 + x / 3) && (x > 3*y - 700)) {
            vx -= turnFactor;
            vy += turnFactor;
        }
        if ((y > 700 / 3 + x / 3) && (x < 3*y - 700)) {
            vx += turnFactor;
            vy -= turnFactor;
        }*/

        /*if ((y < 400) && (x > 800)) {
            vy += turnFactor;
        } else if ((y > 500) && (x < 1100)) {
            vy -= turnFactor;
        }*/
        /*if ((y < 500) && (x < 1100) && (x > 800)) {
            vx += turnFactor;
            vy += turnFactor;
        }
        if ((y > 500) && (x < 1100) && (x > 800)) {
            vx += turnFactor;
            vy -= turnFactor;
        }*/
        /*if (vy > 0) {
            if ((y > 400) && (x < 1100) && (x > 800)) {
                vy += turnFactor;
            }
            *//*if ((y > 500)) {
                vy += turnFactor;
            }*//*
        }
        if (vy < 0) {
            *//*if ((y < 400)) {
                vy -= turnFactor;
            }*//*
            if ((y < 500) && (x < 1100) && (x > 800)) {
                vy -= turnFactor;
            }
        }*/

        //position = new Vec2(x, y);
        velocity = new Vec2(vx, vy);
    }

    public void draw(Graphics2D g2) {
        g2.setColor(boidColour);
        double height = 5, half = height / 2;
        int x[] = {
                (int) (position.x() + height * Math.sin(getDirection())*2),
                (int) (position.x() + height * Math.sin(getDirection() + half)*2),
                (int) (position.x() + height * Math.sin(getDirection() - half)*2)
        };
        int y[] = {
                (int) (position.y() + height * Math.cos(getDirection())*2),
                (int) (position.y() + height * Math.cos(getDirection() + half)*2),
                (int) (position.y() + height * Math.cos(getDirection() - half)*2)
        };
        g2.fill(new Polygon(x, y, x.length));
    }
    private double getDirection() {
        return new Vec2().angleBetween(velocity);
    }
    public void setLeader(LeaderBoid leader){
        this.leader = leader;
        hasLeader = true;
    }
    public boolean hasLeader(){
        return hasLeader;
    }
    public void recieveMessage(Hashtable<String, Vec2> message) {
        leaderPosition = message.get("Position");
        leaderVelocity = message.get("Velocity");
        //System.out.println(leaderPosition);
    }
    public void setColor(Color color){
        this.boidColour = color;
    }

    public Vec2 getLeaderPos() {
        return leaderPosition;
    }
    /*public Vec2 getLeaderVel() {
        return leaderVelocity;
    }*/

    public void setNumber (int number) {
        this.number = number;
    }

    public int getNumber() {
        return number;
    }
    public void setNumberOfBoids(int num_boids) {
        this.num_boids = num_boids;
    }
    public int getNumberOfBoids() {
        return num_boids;
    }
}

