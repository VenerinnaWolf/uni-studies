package boids;
import java.util.ArrayList;
public abstract class Behaviour { //TODO consider an interface
    private int radius;
    private double angle, weight;
    private boolean invert = false;
    public Behaviour(int radius, double angle, double weight) {
        if (0.0 > angle) {
            angle = 0.0;
        } else if (Math.PI < angle) {
            angle = Math.PI;
        }
        this.radius = radius;
        this.angle = angle;
        this.weight = weight;
    }
    private boolean isNearby(Boid a, Boid b) {
        if (a == b) {
            return false;
        }
        if ((a.pos().minus(b.pos()).magnitude() < radius) && (b.vel().absAngleBetween(a.pos().minus(b.pos())) < angle)) {
        //if ((a.pos().minus(b.pos()).magnitude() < radius) && (b.vel().absAngleBetween(a.vel()) < angle)) {
            return true;
        }
        return false;
    }
    private boolean isNearby(Boid a, LeaderBoid b) {
        if (a == b) {
            return false;
        }
        if ((a.pos().minus(b.pos()).magnitude() < radius) && (b.vel().absAngleBetween(a.pos().minus(b.pos())) < angle)) {
            return true;
        }
        return false;
    }
    public ArrayList<Boid> getNearbyBoids(ArrayList<Boid> boids, Boid current) {
        ArrayList<Boid> nearbyBoids = new ArrayList<Boid>();
        if (null != boids && null != current && radius != 0 && angle != 0.0) {
            for (Boid boid : boids) {
                if (/*boid != current &&*/ isNearby(boid, current)) {
                    nearbyBoids.add(boid);
                }
            }
        }
        return nearbyBoids;
    }
    public ArrayList<LeaderBoid> getNearbyBoids(ArrayList<LeaderBoid> boids, LeaderBoid current) {
        ArrayList<LeaderBoid> nearbyBoids = new ArrayList<LeaderBoid>();

        if (null != boids && null != current && radius != 0 && angle != 0.0) {
            for (LeaderBoid boid : boids) {
                if (/*boid != current && */isNearby(boid, current)) {
                    nearbyBoids.add(boid);
                }
            }
        }
        return nearbyBoids;
    }
    public abstract Vec2 getForce(ArrayList<Boid> nearbyBoids, Boid current);
    public abstract Vec2 getLeaderForce(ArrayList<LeaderBoid> nearbyBoids, LeaderBoid current);
    public void apply(ArrayList<Boid> boids, Boid boid) {
        Vec2 force = getForce(getNearbyBoids(boids, boid), boid);
        boid.applyForce(force.scale(weight));
    }
    public void applyLeader(ArrayList<LeaderBoid> boids, LeaderBoid leader) {
        Vec2 force = getLeaderForce(getNearbyBoids(boids, leader), leader);
        leader.applyForce(force.scale(weight));
    }
    public double radius() {
        return radius;
    }
    /*public boolean isInverted() {
        return invert;
    }
    public void invert(boolean invert) {
        this.invert = invert;
    }*/
}
