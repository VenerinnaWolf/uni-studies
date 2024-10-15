package boids;
import java.util.ArrayList;
import java.util.Hashtable;
public class LeaderBoid extends Boid {
    private ArrayList<Boid> followers = new ArrayList<>();
    public LeaderBoid() {
        super();
    }
    public void attractFollower(ArrayList<Boid> nearbyBoids) {
        if (null == nearbyBoids || followers.size() >= 50) {
            return;
        }
        if (0 != nearbyBoids.size()) {
            for (Boid boid : nearbyBoids) {
                if(boid.hasLeader() == false){
                    followers.add(boid);
                    boid.setLeader(this);
                }
            }
        }
    }
    public void beginCommunication() {
        for (Boid boid : followers) {
            boid.recieveMessage(sendMessage());
        }
    }
    public Hashtable<String, Vec2> sendMessage() {
        Hashtable<String, Vec2> message = new Hashtable<>();
        message.put("Velocity", vel());
        message.put("Position", pos());
        //System.out.println(message);
        return message;
    }
}