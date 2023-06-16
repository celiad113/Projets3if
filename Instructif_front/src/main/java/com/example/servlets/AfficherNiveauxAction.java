package com.example.servlets;

import metiers.Niveau;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.util.List;

public class AfficherNiveauxAction extends Action{
    @Override
    public void execute(HttpServletRequest request) {
        HttpSession session = request.getSession(false);

        List<Niveau> niveaux = sc.tousNiveau();
        session.setAttribute("niveaux", niveaux);

    }
}
