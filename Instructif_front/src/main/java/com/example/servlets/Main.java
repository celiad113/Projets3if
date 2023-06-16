package com.example.servlets;

import dao.JpaUtil;
import metiers.Eleve;
import metiers.Service;

import java.util.List;

public class Main {
    public static void main(String[] args) {
        annulerCours();
    }

    public static void annulerCours(){
        JpaUtil.creerFabriquePersistance();
        Service sc = new Service();
        Eleve eleve = sc.authentificationEleve("ick62377@gmail.com", "nounouheros");
        sc.terminerVisio(eleve.getCoursActuel());
        JpaUtil.fermerFabriquePersistance();
    }
}
