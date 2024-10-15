package boids;
import java.util.ArrayList;
public class AvoidPoint extends Behaviour {
    private Vec2 point;
    private String shape;
    private boolean active;
    public AvoidPoint(int radius, double angle, double weight) {
        super(radius, angle, weight);
        point = new Vec2();
        shape = "";
        active = false;
    }
    @Override
    public Vec2 getForce(ArrayList<Boid> nearbyBoids, Boid current) {
        /*if (current == null) {
            return new Vec2();
        }
        Vec2 avoid = current.pos().minus(point);

        double lenSq = avoid.magnitude();
        if (lenSq <= 1.72*radius()) {
            return avoid.scale(radius());
        } else {
            return new Vec2();
        }*/

        if (current == null) {
            return new Vec2();
        }
        Vec2 avoid = current.pos().minus(point);
        double lenSq = avoid.magnitude();
        //System.out.println(shape);
        if ((shape == "Oval")
                && ((current.pos().x() - point.x()) * (current.pos().x() - point.x())
                + (current.pos().y() - point.y()) * (current.pos().y() - point.y())
                <= 1.72 * 1.72 * radius() * radius())) {
            return avoid.scale(radius());
        }
        if ((shape == "Triangle")
                && (current.pos().y() >= point().y() - 2.2 * radius())
                && ((current.pos().y() - (point.y() + 2 * 2.2 * radius())) <= (((point.y() - 2.2 * radius())
                - (point.y() + 2 * 2.2 * radius())) / ((point.x() - Math.sqrt(3) * 2.2 * radius())
                - point.x())) * (current.pos().x() - point.x()))
                && ((current.pos().y() - (point.y() + 2 * 2.2 * radius())) <= (((point.y() - 2.2 * radius())
                - (point.y() + 2.2 * 2 * radius())) / ((point.x() + Math.sqrt(3) * 2.2 * radius())
                - point.x())) * (current.pos().x() - point.x()))) {
            return avoid.scale(radius());
        }
        if ((shape == "Square")
                && ((current.pos().y()) >= (point.y() - 2 * radius())) && ((current.pos().y())
                <= (point.y() + 2 * radius())) && ((current.pos().x()) <= (point.x() + 2 * radius()))
                && ((current.pos().x()) >= (point.x() - 2 * radius()))) {
            return avoid.scale(radius());
        /*}
        if ((shape == "tunnel")
                && ((current.pos().y()) >= 400) && ((current.pos().y())
                <= 500) && (current.pos().x() <= 1100) && (current.pos().x() >= 800)) {
            return avoid.scale(radius());*/
        } else {
            return new Vec2();
        }
    }
    @Override
    public Vec2 getLeaderForce(ArrayList<LeaderBoid> nearbyBoids, LeaderBoid current) {
        if (current == null) {
            return new Vec2();
        }
        Vec2 avoid = current.pos().minus(point);
        //double lenSq = avoid.magnitude();
        if ((shape == "Oval")
                && ((current.pos().x() - point.x()) * (current.pos().x() - point.x())
                + (current.pos().y() - point.y()) * (current.pos().y() - point.y())
                <= 1.72 * 1.72 * radius() * radius())) {
            return avoid.scale(radius());
        }
        if ((shape == "Triangle")
                && (current.pos().y() >= point().y() - 2.2 * radius())
                && ((current.pos().y() - (point.y() + 2 * 2.2 * radius())) <= (((point.y() - 2.2 * radius())
                - (point.y() + 2 * 2.2 * radius())) / ((point.x() - Math.sqrt(3) * 2.2 * radius())
                - point.x())) * (current.pos().x() - point.x()))
                && ((current.pos().y() - (point.y() + 2 * 2.2 * radius())) <= (((point.y() - 2.2 * radius())
                - (point.y() + 2.2 * 2 * radius())) / ((point.x() + Math.sqrt(3) * 2.2 * radius())
                - point.x())) * (current.pos().x() - point.x()))) {
            return avoid.scale(radius());
        }
        if ((shape == "Square")
                && ((current.pos().y()) >= (point.y() - 2 * radius())) && ((current.pos().y())
                <= (point.y() + 2 * radius())) && ((current.pos().x()) <= (point.x() + 2 * radius()))
                && ((current.pos().x()) >= (point.x() - 2 * radius()))) {
            return avoid.scale(radius());
        /*}
        if ((shape == "tunnel")
                && ((current.pos().y()) >= 400) && ((current.pos().y())
                <= 500) && (current.pos().x() <= 1100) && (current.pos().x() >= 800)) {
            return avoid.scale(radius());*/
        } else {
            return new Vec2();
        }
    }
    public void updatePoint(double x, double y) {
        point = new Vec2(x, y);
    }

    public Vec2 point() {
        return point;
    }

    public String getShape() {
        return shape;
    }
    public void setShape(String shape) {
        this.shape = shape;
    }
    public void setActive(boolean active) {
        this.active = active;
    }
}
