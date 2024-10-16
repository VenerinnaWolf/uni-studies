package boids;
import java.util.ArrayList;
public class Alignment extends Behaviour {
    public Alignment(int radius, double angle, double weight) {
        super(radius, angle, weight);
    }

    @Override
    public Vec2 getForce(ArrayList<Boid> nearbyBoids, Boid current) {
        if (null == nearbyBoids || null == current) {
            return new Vec2();
        }
        Vec2 sum = new Vec2();
        for (Boid boid : nearbyBoids) {
            sum = sum.plus(boid.vel());
        }
        if (0 != nearbyBoids.size()) {
            sum = sum.scale(1.0 / nearbyBoids.size());
        }
        return sum;
    }

    @Override
    public Vec2 getLeaderForce(ArrayList<LeaderBoid> nearbyBoids, LeaderBoid current) {
        if (null == nearbyBoids || null == current) {
            return new Vec2();
        }
        Vec2 sum = new Vec2();
        for (LeaderBoid leader : nearbyBoids) {
            sum = sum.plus(leader.vel());
        }
        if (0 != nearbyBoids.size()) {
            sum = sum.scale(1.0 / nearbyBoids.size());
        }
        return sum;
    }
}