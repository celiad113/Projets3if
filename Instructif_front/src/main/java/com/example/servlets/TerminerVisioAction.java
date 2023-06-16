package com.example.servlets;

import metiers.Cours;
import metiers.Eleve;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

public class TerminerVisioAction extends Action{

    @Override
    public void execute(HttpServletRequest request) {
        HttpSession session = request.getSession(false);
        Eleve eleve = (Eleve)session.getAttribute("eleve");

        Cours cours = eleve.getCoursActuel();

        session.setAttribute("cours", cours);

        System.out.println(cours);

        if (cours != null) {
            sc.terminerVisio(cours);
            String email = eleve.getMail();
            String password = eleve.getMotDePasse();
            eleve = sc.authentificationEleve(email, password);
            session.setAttribute("eleve", eleve);
        }

        System.out.println("Fin du cours de " + eleve.getPrenom());
    }
}
