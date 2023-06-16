package com.example.servlets;

import metiers.Eleve;
import metiers.Niveau;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.time.ZoneId;
import java.time.format.DateTimeFormatter;
import java.util.Date;

public class InscriptionEleveAction extends Action{
    @Override
    public void execute(HttpServletRequest request) {
        HttpSession session = request.getSession(false);

        String email = request.getParameter("email");
        String password = request.getParameter("password");
        String firstName = request.getParameter("firstName");
        String lastName = request.getParameter("lastName");
        String code = request.getParameter("code");

        System.out.println(request.getParameter("class"));
        Long niveau = Long.parseLong(request.getParameter("class"));
        String date = request.getParameter("date");

        Eleve eleve;

        DateFormat inputDateFormat = new SimpleDateFormat("yyyy-MM-dd");
        try {
            date = new SimpleDateFormat("yyyy/MM/dd").format(inputDateFormat.parse(date));
        } catch (ParseException e) {
            date = "2002/06/09";
        }

        try {
            eleve = new Eleve(lastName, firstName, date, email, password, sc.trouverNiveau(niveau));
            sc.inscriptionEleve(eleve, code);
        } catch (Exception e) {
            eleve = null;
        }
        session.setAttribute("eleve", eleve);
        session.setAttribute("operation", "inscription");

    }
}
