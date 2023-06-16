package com.example.servlets;

import metiers.Intervenant;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

public class AuthentifierEnseignantAction extends Action{
    @Override
    public void execute(HttpServletRequest request) {
        HttpSession session = request.getSession(false);

        String login = request.getParameter("login");
        String password = request.getParameter("password");

        Intervenant intervenant = sc.authentificationIntervenant(login, password);


        if(intervenant != null){
            session.setAttribute("intervenant", intervenant);
        }
        else{
            System.out.println("Echec de l'authentification");
        }
    }
}
