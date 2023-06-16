package com.example.servlets;

import metiers.Cours;
import metiers.Intervenant;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

public class CoursIntervenantEnAttente extends Action{
    @Override
    public void execute(HttpServletRequest request) {
        HttpSession session = request.getSession(false);

        Long intervenantId = ((Intervenant)session.getAttribute("intervenant")).getId();

        // On cherche la version de l'intervenant qui est persistée dans la base de donnée (celui de la session ne se fait pas update automatiquement)
        Intervenant intervenant = sc.trouverIntervenantParId(intervenantId);

        // On update l'attribut intervenant pour avoir la version mise à jour
        session.setAttribute("intervenant", intervenant);

        Cours coursActuel = intervenant.getCoursActuel();

        session.setAttribute("coursActuel",coursActuel);
    }
}
