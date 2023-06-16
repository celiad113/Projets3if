package com.example.servlets;

import metiers.Eleve;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

public class AuthentifierEleveAction extends Action{

    @Override
    public void execute(HttpServletRequest request) {

        HttpSession session = request.getSession(false);
        String login = request.getParameter("login");
        String password = request.getParameter("password");

        Eleve eleve = sc.authentificationEleve(login, password);

        if(eleve != null){
            session.setAttribute("eleve" , eleve);
        }else{
            System.out.println("Echec de l'authentification");
            session.setAttribute("eleve", null);
        }
        session.setAttribute("operation", "connexion");

    }

}
