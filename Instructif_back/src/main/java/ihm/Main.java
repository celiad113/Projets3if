package ihm;

import dao.JpaUtil;
import java.io.IOException;
import java.text.ParseException;
import java.util.List;
import metiers.Cours;
import metiers.Intervenant;
import metiers.Service;
import metiers.Eleve;
import metiers.Etablissement;
import metiers.Matiere;
import metiers.Saisie;
import metiers.Niveau;
import static metiers.Saisie.lireChaine;
import static metiers.Saisie.lireInteger;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author relmir
 */
public class Main {

    public static void main(String[] args) throws ParseException, IOException {
        JpaUtil.creerFabriquePersistance();
        initialisationTest();
        JpaUtil.fermerFabriquePersistance();
    }


    public static void initialisationTest() throws ParseException, IOException {
        Service s = new Service();

        //initialisation des niveaux
        s.initialiserNiveau();
        //initialisation des matières
        s.initialiserMatiere();

        //inscription préalable de 3 élèves venant de 2 lycées différents.

        Eleve e1 = new Eleve("Dupont", "Robert", "1999/02/12", "rdupont@gmail.com", "mdp", s.trouverNiveau(7L));
        s.inscriptionEleve(e1, "0921159K");
        Eleve e2 = new Eleve("Leroux", "Lou", "1999/02/12", "llerouxt@gmail.com", "mdp", s.trouverNiveau(4L));
        s.inscriptionEleve(e2, "0332490C");
        Eleve e3 = new Eleve("Blanc", "Chantal", "2004/07/05", "cblanc@gmail.com", "mdp", s.trouverNiveau(5L));
        s.inscriptionEleve(e3, "0332490C");
        Eleve e4 = new Eleve("Noir", "Chantal", "2004/07/05", "cnoir@gmail.com", "mdp", s.trouverNiveau(5L));
        s.inscriptionEleve(e4, "0332490C");

        //inscription de quelques intervenants
        s.initialiserIntervenant();
        
        //demande de cours de niveau 5, utile pour le test d'intervenant dans la suite
        s.effectuerDemandeCours(e3, 13L, "Bonjour, c'est la premiere demande de cours sur la plateforme!");
        
        System.out.println("Boujour et Bienvenue sur INSTRUCT'IF.\n");
        //Presentation des niveaux
        List<Niveau> listNiveau = s.tousNiveau();
        System.out.println("Il y a 7 niveaux disponibles sur l'application : \n");
        for (Niveau n : listNiveau) {
            System.out.println(n);
        }
        //Presentation des matières
        List<Matiere> listMatiere = s.toutesMatiere();
        System.out.println("Il y a 10 matières disponibles sur l'application : \n");
        for (Matiere m : listMatiere) {
            System.out.println(m);
        }

        //Presentation des élèves et intervenants
        System.out.println(" Il y a déjà 3 élèves inscrits ainsi que 5 intervenants");
        List<Eleve> le = s.tousEleve();
        for (Eleve e : le) {
            System.out.println(e.toString());
        }
        List<Intervenant> li = s.tousIntervenants();
        for (Intervenant i : li) {
            System.out.println(i.toString());
        }

        System.err.println("Tout le monde a été initialisé");
    }

    public static void testerInscriptionEleveSaisie() throws ParseException, IOException {
        Service s = new Service();

        System.out.println("Veuillez inscrire un Eleve:");

        String prenom = Saisie.lireChaine("Prenom:");
        String nom = Saisie.lireChaine("Nom:");
        String date = Saisie.lireChaine("Date de naissance:");
        String mail = Saisie.lireChaine("Mail:");
        String mdp = Saisie.lireChaine("Mot de passe:");
        int niveau = Saisie.lireInteger("Numero d'identification du niveau:");
        String etab = Saisie.lireChaine("Numero d'établissement:");

        Eleve e1 = new Eleve(prenom, nom, date, mail, mdp, s.trouverNiveau((long) niveau));
        s.inscriptionEleve(e1, etab);

    }

    public static Eleve testerAuthByEmailEleveSaisie() throws ParseException {
        Service s = new Service();
        Saisie ss = new Saisie();
        System.out.println("Vous pouvez maintenant vous authentifier : ");
        String mail = ss.lireChaine("Mail:");
        String mdp = ss.lireChaine("Mot de passe :");

        Eleve e = s.authentificationEleve(mail, mdp);

        if (e == null) {
            System.out.println("Echec de l'authentification authentification, veuillez ré-essayer");
        } else {
            System.out.println("L'authentification est un succès : " + e);
        }
        return e;
    }

    public static Intervenant testerAuthByEmailIntervenant() throws ParseException {
        Service s = new Service();
        
         Saisie ss = new Saisie();
        System.out.println("Vous pouvez maintenant vous authentifier : ");
        String mail = ss.lireChaine("Mail:");
        String mdp = ss.lireChaine("Mot de passe :");


        Intervenant in = s.authentificationIntervenant(mail, mdp);
        if (in == null) {
            System.out.println("Echec de l'authentification authentification, veuillez ré-essayer");
        } else {
            System.out.println("L'authentification est un succès : " + in);
        }
        return in;
    }

    public static void testFinalDemandeCoursEleve(Eleve e1) throws IOException {

        Service s = new Service();
        //le premier eleve inscrit dans la base de données va faire une demande de cours
        
        System.out.println("Tu es l'élève " + e1.getNom() + " " + e1.getPrenom() + " en " + e1.getNiveauScolaire() + " Tu veux demander un cours de soutien dans quelle matière ?");
        List<Matiere> listMatiere = s.toutesMatiere();
        System.out.println("Il y a 11 matières disponibles sur l'application : \n");
        for (Matiere m : listMatiere) {
            System.out.println(m);
        }
        Integer mat = lireInteger("Je choisis l'id matière :");

        String detail = lireChaine("Ecris l'objet de ta demande : ");
        Cours cours = s.effectuerDemandeCours(e1, s.trouverMatiere(Long.valueOf(mat)).getId(), detail);

        if (cours != null) {
            lireChaine("Ta demande de cours va être satisfaite : tu as cours avec " + cours.getIntervenant().toString());

            System.out.println("Entrez 0 quand la visio est terminée");
            int fin = lireInteger("Visio finie ? : ");
            if (fin == 0) {
                s.terminerVisio(cours);
                System.out.println("Donnez une note au cours :\n 1,2,3,4 ou 5?");
                int note = lireInteger("Note : ");
                testNote(cours, note);

            }

        } else {
            System.out.println("Aucun prof disponible n'a été trouvé, ré-essaie dans 15 minutes");
        }

    }

    public static void testFinalDemandeCoursIntervenant(Intervenant i) {
        Service s = new Service();
        //le premier eleve inscrit dans la base de données va faire une demande de cours
        Eleve e1 = s.tousEleve().get(2);

        Cours cours = i.getCoursActuel();
        
        if (cours != null) {
            Integer infossup = lireInteger("Bonjour ! Vous avez une demande de cours en attente ! \nTapez 1 si vous voulez des informations supplémentaires sur l'élève : ");
            if (infossup == 1) {
                System.out.println(e1.toString());
            }
            Integer infossup2 = lireInteger("Tapez 2 pour accéder à la visio :");
            if (infossup2 == 2) {
                System.out.println("Vous accédez à la visio");
            }
            
            s.terminerVisio(cours);

            System.out.println("La visio a été terminée par l'élève");
            //testerHistoriqueIntervenant(cours.getIntervenant());
        }else {
            System.out.println("Bonjour, vous n'avez pas de demande de cours en attente.");
        }

        
    }

    public static void testAutreDemandeCours() throws IOException {

        System.out.println("Je réalise une deuxieme demande pour le même cours pour montrer que l'on change d'intervenant en fonciton du nombre de cours qu'il a déjà fait");
        Service s = new Service();
        //le premier eleve inscrit dans la base de données va faire une demande de cours
        Eleve e1 = s.tousEleve().get(3);
        System.out.println("Tu es l'élève10" + e1.getNom() + " " + e1.getPrenom() + " en " + e1.getNiveauScolaire() + " Tu veux demander un cours de soutien dans quelle matière ?");
        List<Matiere> listMatiere = s.toutesMatiere();
        System.out.println("Il y a 11 matières disponibles sur l'application : \n");
        for (Matiere m : listMatiere) {
            System.out.println(m);
        }
        Integer mat = lireInteger("Je choisis l'id matière :");

        String detail = lireChaine("Ecris l'objet de ta demande : ");
        Cours cours = s.effectuerDemandeCours(e1, s.trouverMatiere(Long.valueOf(mat)).getId(), detail);

        if (cours != null) {
            lireChaine("Ta demande de cours va être satisfaite : tu as cours avec " + cours.getIntervenant().toString());

            System.out.println("Entrez 0 quand la visio est terminée");
            int fin = lireInteger("Visio finie ? : ");
            if (fin == 0) {
                s.terminerVisio(cours);
                System.out.println("Donnez une note au cours :\n 1,2,3,4 ou 5?");
                int note = lireInteger("Note : ");
                testNote(cours, note);

            }

        } else {
            System.out.println("Aucun prof disponible n'a été trouvé, ré-essaie dans 15 minutes");
        }

        testerHistoriqueEleve(e1);

    }



    public static void testerHistoriqueIntervenant(Intervenant i) {
        lireChaine("Voulez-vous voir votre historique Intervenant? ");
        Service s = new Service();

        List<Cours> c = i.getCours();
        for (Cours cr : c) {
            System.out.println(cr);
        }

    }

    public static void testerHistoriqueEleve(Eleve e) {
        lireChaine("Voulez-vous voir votre historique Eleve ?");
        Service s = new Service();

        List<Cours> c = e.getCours();
        for (Cours cr : c) {
            System.out.println(cr);
        }

    }

    public static void testNote(Cours c, int note) {
        Service s = new Service();
        if (s.noterUnCours(c, note)) {
            System.out.println("Vous avez donné la note de " + note + " au cours.");

        } else {
            System.out.println("Veuillez renseigner une note entre 0 et 5");
        }

    }

    public static void testStatistiques() {
        lireChaine("Voulez-vous voir les statistics de la plateforme? ");
        Service s = new Service();
        System.out.println("Nombre d'eleves inscrits sur INSTRUCT'IF : " + s.compterEleves());
        System.out.println("Nombre d'eleves inscrits dans des etablissements ayant un IPS inferieur a 81 : " + s.compterElevesIpsBas(81));
        System.out.println("Nombre total de demandes de soutien traitees sur INSTRUCT'IF : " + s.compterCoursTotal());
        System.out.println("Nombre total de demandes de soutien traitees aujourd'hui : " + s.compterCoursDuJours());
        System.out.println("Coordonnees geographiques des etablissements des eleves inscrits sur INSTRCUT'IF : ");
        List<Etablissement> liste = s.listeTousEtablissements();
        for (Etablissement e : liste) {
            System.out.println(e.getNom() + " , Longitude : " + e.getLongitude() + " , Latitude : " + e.getLatitude());
        }
        System.out.println("Coordonnees geographiques des etablissements ayant un IPS inferieur a 81 : ");
        List<Etablissement> liste2 = s.listeEtablissementsIpsBas(81);
        for (Etablissement e : liste2) {
            System.out.println(e.getNom() + " , Longitude : " + e.getLongitude() + " , Latitude : " + e.getLatitude());
        }
    }
}
