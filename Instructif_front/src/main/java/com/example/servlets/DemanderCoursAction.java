package com.example.servlets;

import metiers.Cours;
import metiers.Eleve;
import metiers.Matiere;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.util.List;

public class DemanderCoursAction extends Action{

    @Override
    public void execute(HttpServletRequest request) {

        HttpSession session = request.getSession(false);

        Eleve eleve = (Eleve) session.getAttribute("eleve");
        String mailEleve = eleve.getMail();
        String motDePasseEleve = eleve.getMotDePasse();

        String matiere = request.getParameter("matiere");
        String message = request.getParameter("message");

        Long matiereId = Long.parseLong(matiere);

        Cours cours = sc.effectuerDemandeCours(eleve, matiereId, message);

        // Update de l'attribut élève
        eleve = sc.authentificationEleve(mailEleve, motDePasseEleve);
        session.setAttribute("eleve", eleve);

        if (cours != null) {
            session.setAttribute("cours", cours);
        } else {
            System.out.println("Demande refusée");
            session.setAttribute("cours", null);
        }

    }

    public void listMatiere(HttpServletRequest request){
        List<Matiere> matieres = sc.toutesMatiere();
        request.setAttribute("matieres", matieres);
    }

}
