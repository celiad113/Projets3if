package com.example.servlets;

import metiers.Cours;
import metiers.Eleve;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

public class NoterCoursAction extends Action{

    @Override
    public void execute(HttpServletRequest request) {
        HttpSession session = request.getSession(false);

        Cours cours = (Cours)session.getAttribute("cours");

        System.out.println(cours);

        int note = Integer.parseInt(request.getParameter("note"));

        if (cours!=null)
        {
            sc.noterUnCours(cours, note);
        }
    }
}
