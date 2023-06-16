package com.example.servlets;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.util.Enumeration;

public class DeconnexionAction extends Action {
    @Override
    public void execute(HttpServletRequest request) {
        HttpSession session = request.getSession(false);

        Enumeration<String> attributeNames = session.getAttributeNames();

        while(attributeNames.hasMoreElements()){
            String attributeName = attributeNames.nextElement();

            session.removeAttribute(attributeName);
        }

        session.invalidate();
    }
}
