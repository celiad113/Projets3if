package util;

import metiers.Intervenant;

import javax.servlet.annotation.WebListener;
import javax.servlet.http.HttpSession;
import javax.servlet.http.HttpSessionEvent;
import javax.servlet.http.HttpSessionListener;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

@WebListener
public class HttpSessionCollector implements HttpSessionListener {
    private static final Map<String, HttpSession> SESSIONS = new ConcurrentHashMap<>();

    @Override
    public void sessionCreated(HttpSessionEvent event) {
        HttpSession session = event.getSession();
        SESSIONS.put(session.getId(), session);
    }


    @Override
    public void sessionDestroyed(HttpSessionEvent event) {
        SESSIONS.remove(event.getSession().getId());
    }

    public static HttpSession findSessionIntervenant(String intervenantId){

        for (ConcurrentHashMap.Entry<String, HttpSession> entry : SESSIONS.entrySet()) {
            String key = entry.getKey();
            HttpSession session = entry.getValue();

            if(((Intervenant) session.getAttribute("intervenant")).getId().toString().equals(intervenantId)){
                return session;
            }
        }

        return null;
    }
    public static HttpSession find(String sessionId) {
        return SESSIONS.get(sessionId);
    }
}
