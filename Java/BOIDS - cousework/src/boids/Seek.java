package boids;
import java.util.ArrayList;
public class Seek extends Behaviour {
    private Vec2 point;
    private Vec2 leaderPosition;
    private Vec2 leaderVelocity;
    private boolean active;
    private int count;
    public Seek(int radius, double angle, double weight) {
        super(radius, angle, weight);
        active = false;
        point = new Vec2();
        leaderPosition = new Vec2();
        leaderVelocity = new Vec2();
    }
    @Override
    public Vec2 getForce(ArrayList<Boid> nearbyBoids, Boid current) {
        if (current == null) {
            return new Vec2();
        }
        count = current.getNumberOfBoids();
        //System.out.println(count);
        Vec2 seek = new Vec2();
        Vec2 dif = point.minus(current.pos());
        double lensq = dif.magnitude();
        if (lensq <= radius()) {
            if (current.getNumber() <= count / 3 - 1) {
                seek = new Vec2(dif.x(),dif.y() - 3*radius()/4);
                /*if (((current.pos().x() - point.x()) * (current.pos().x() - point.x())
                        + (current.pos().y() - (point.y() - 3*radius()/4)) * (current.pos().y() - (point.y() - 3*radius()/4))
                        <= 1.72 * 1.72 * 3*radius()/4 * 3*radius()/4)) {
                    seek = seek.scale(1 / (1.1-1));
                }*/
            }
            if ((current.getNumber() <= 2 * count / 3 - 1) && (current.getNumber() > count / 3 - 1)) {
                seek = new Vec2(dif.x(), dif.y() + 3*radius() / 4);
            }
            if ((current.getNumber() <= count - 1) && (current.getNumber() > 2 * count / 3 - 1)) {
                seek = new Vec2(dif.x()+ 3*radius() / 4, dif.y() );
            }
        } else {
            seek = current.getLeaderPos().minus(current.pos());
        }
        return seek;
    }
    @Override
    public Vec2 getLeaderForce(ArrayList<LeaderBoid> nearbyBoids, LeaderBoid current) {
        if (current == null) {
            return new Vec2();
        }
        Vec2 seek = point.minus(current.pos());
        return seek;
    }

    public Vec2 point() {
        return point;
    }
    public void updatePoint(double x, double y) {
        point = new Vec2(x, y);
    }
    public void setActive(boolean active) {
        this.active = active;
    }
    public boolean isActive() {
        return active;
    }
}