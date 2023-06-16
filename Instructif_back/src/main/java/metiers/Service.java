/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package metiers;

import com.google.maps.model.LatLng;
import dao.CoursDao;
import dao.EleveDao;
import dao.IntervenantDao;
import dao.EtablissementDao;
import dao.JpaUtil;
import dao.MatiereDao;
import dao.NiveauDao;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import javax.persistence.OptimisticLockException;

/**
 *
 * @author relmir
 */
public class Service {

    public Service() {
    }

    public List<Etablissement> listeEtablissementsIpsBas(double ips) {
        EtablissementDao eDao = new EtablissementDao();
        List<Etablissement> l = new ArrayList();
        try {
            JpaUtil.creerContextePersistance();
            l = eDao.findAll(1, ips);
        } catch (Exception ex) {
            ex.printStackTrace();
            JpaUtil.annulerTransaction();

        } finally {
            JpaUtil.fermerContextePersistance();
        }
        return l;
    }

    public List<Etablissement> listeTousEtablissements() {
        EtablissementDao eDao = new EtablissementDao();
        List<Etablissement> l = new ArrayList();
        try {
            JpaUtil.creerContextePersistance();
            l = eDao.findAll(0, 0);
        } catch (Exception ex) {
            ex.printStackTrace();
            JpaUtil.annulerTransaction();

        } finally {
            JpaUtil.fermerContextePersistance();
        }
        return l;
    }


    public long compterCoursDuJours() {
        CoursDao cDao = new CoursDao();
        long count = -1;
        try {
            JpaUtil.creerContextePersistance();
            count = cDao.countToday().get(0);
        } catch (Exception ex) {
            ex.printStackTrace();
            JpaUtil.annulerTransaction();

        } finally {
            JpaUtil.fermerContextePersistance();
        }
        return count;
    }

    public long compterCoursTotal() {
        CoursDao cDao = new CoursDao();
        long count = -1;
        try {
            JpaUtil.creerContextePersistance();
            count = cDao.count().get(0);
        } catch (Exception ex) {
            ex.printStackTrace();
            JpaUtil.annulerTransaction();

        } finally {
            JpaUtil.fermerContextePersistance();
        }
        return count;
    }

    public long compterEleves() {
        EleveDao eDao = new EleveDao();
        long count = -1;
        try {
            JpaUtil.creerContextePersistance();
            count = eDao.count(0, 0.0).get(0);
        } catch (Exception ex) {
            ex.printStackTrace();
            JpaUtil.annulerTransaction();

        } finally {
            JpaUtil.fermerContextePersistance();
        }
        return count;
    }

    public long compterElevesIpsBas(double ips) {
        EleveDao eDao = new EleveDao();
        long count = -1;
        try {
            JpaUtil.creerContextePersistance();
            count = eDao.count(1, ips).get(0);
        } catch (Exception ex) {
            ex.printStackTrace();
            JpaUtil.annulerTransaction();

        } finally {
            JpaUtil.fermerContextePersistance();
        }
        return count;
    }

    public boolean terminerVisio(Cours cours) {
        boolean etat = false;

        EleveDao eDao = new EleveDao();
        IntervenantDao iDao = new IntervenantDao();

        try {
            JpaUtil.creerContextePersistance();
            JpaUtil.ouvrirTransaction();
            eDao.updateCoursActuel(cours.getEleve(), null);
            iDao.updateCoursActuelEtDisponibilite(cours.getIntervenant(), null, true);
            JpaUtil.validerTransaction();
            etat = true;
        } catch (Exception ex) {
            ex.printStackTrace();
            JpaUtil.annulerTransaction();

        } finally {
            JpaUtil.fermerContextePersistance();
        }
        return etat;
    }

    public Cours effectuerDemandeCours(Eleve eleve, Long idMatiere, String message) throws OptimisticLockException {
        Cours cours = null;
        Niveau niveauRequis = eleve.getNiveauScolaire();
        List<Intervenant> intervenantsTrouves = null;
        Intervenant intervenantChoisi = null;
        IntervenantDao iDao = new IntervenantDao();
        MatiereDao mDao = new MatiereDao();
        CoursDao cDao = new CoursDao();
        EleveDao eDao = new EleveDao();
        try {
            JpaUtil.creerContextePersistance();
            JpaUtil.ouvrirTransaction();
            intervenantsTrouves = iDao.findByNiveau(niveauRequis);

            if (intervenantsTrouves != null && !intervenantsTrouves.isEmpty() && eleve.getCoursActuel() == null) {
                intervenantChoisi = intervenantsTrouves.get(0);
                cours = new Cours(mDao.findById(idMatiere), eleve, intervenantChoisi, message);
                cDao.create(cours);
                iDao.updateCoursActuelEtDisponibilite(intervenantChoisi, cours, false);
                iDao.addCoursToListIntervenant(intervenantChoisi, cours);
                eDao.updateCoursActuel(eleve, cours);
                eDao.addCoursToListEleve(eleve, cours);
            }
            JpaUtil.validerTransaction();
            if (cours != null) {
                String messageNotif = "Bonjour " + cours.getIntervenant().getPrenom() + "\nMerci de prendre en charge la demande de soutien en \"" + cours.getMatiere().getNomMatiere() + "\" demandee le " + cours.getDate() + " par " + eleve.getPrenom() + " en classe de " + eleve.getNiveauScolaire().getNomNiveau() + ".";
                Message.envoyerNotification(cours.getIntervenant().getTelephonePro(), messageNotif);
            }
        } catch (Exception ex) {
            JpaUtil.annulerTransaction();
            if (ex.getCause() != null) {
                if (ex.getCause().getClass() == OptimisticLockException.class) {
                    cours = effectuerDemandeCours(eDao.findById(eleve.getId()), idMatiere, message);
                } else {
                    ex.printStackTrace();
                }
            } else {
                ex.printStackTrace();
            }
        } finally {
            JpaUtil.fermerContextePersistance();
        }

        return cours;
    }

    public boolean initialiserIntervenant() {
        IntervenantDao emDao = new IntervenantDao();
        NiveauDao nvdao = new NiveauDao();
        boolean etat = false;
        Intervenant e1 = new Etudiant("FAVRO", "Samuel", "0642049305", "sfavro@gmail.com", "mdp1", "INSA", "Informatique");
        Intervenant e2 = new Autre("DEKEW", "Simon", "0713200950", "sdekew4845@gmail.com", "mdp1", "Chercheur");
        Intervenant e3 = new Enseignant("LOU", "Flavien", "0437340532", "flavien.lou@gmail.com", "mp1", "Lycee");
        Intervenant e4 = new Etudiant("GUOGUEN", "Gabriela", "0719843316", "gguoguen2418@gmail.com", "mdp1", "ENSIMAG", "Chimie");
        Intervenant e5 = new Autre("HERNENDEZ", "Vincent", "0441564193", "vhernendez@gmail.com", "mdp1", "Ingenieur");

        try {
            JpaUtil.creerContextePersistance();
            JpaUtil.ouvrirTransaction();
            e1.addNiveauToList(nvdao.findById(1l));
            e1.addNiveauToList(nvdao.findById(2l));
            e2.addNiveauToList(nvdao.findById(3l));
            e2.addNiveauToList(nvdao.findById(6l));
            e3.addNiveauToList(nvdao.findById(4l));
            e3.addNiveauToList(nvdao.findById(2l));
            e4.addNiveauToList(nvdao.findById(1l));
            e4.addNiveauToList(nvdao.findById(3l));
            e5.addNiveauToList(nvdao.findById(5l));
            emDao.create(e1);
            emDao.create(e2);
            emDao.create(e3);
            emDao.create(e4);
            emDao.create(e5);
            JpaUtil.validerTransaction();
            etat = true;
        } catch (Exception ex) {
            ex.printStackTrace();
            JpaUtil.annulerTransaction();

        } finally {
            JpaUtil.fermerContextePersistance();
        }
        return etat;
    }

    public boolean inscriptionEleve(Eleve eleve, String code) throws IOException {
        EtablissementDao etDao = new EtablissementDao();
        EducNetApi api = new EducNetApi();
        EleveDao elDao = new EleveDao();
        boolean etat = false;
        try {
            JpaUtil.creerContextePersistance();
            List<String> result = api.getInformationCollege(code);
            if (result == null) {
                result = api.getInformationLycee(code);

                if (result == null) {
                    Message.envoyerMail("rol@moi.com", eleve.getMail(), "Echec d'inscription", "L'inscription est un echec");
                    return false;
                }
            }
            String uai = result.get(0);
            String nom = result.get(1);
            String nomCommune = result.get(4);
            double ips = Double.parseDouble(result.get(8));
            String query = nom + "," + nomCommune;
            LatLng coordsEtablissement = GeoNetApi.getLatLng(query);

            Etablissement et = new Etablissement(code, ips, nom, nomCommune, coordsEtablissement.lng, coordsEtablissement.lat);
            JpaUtil.ouvrirTransaction();

            if (etDao.findByCode(code).isEmpty()) {
                etDao.create(et);
            }
            eleve.setEtablissement(etDao.findByCode(code).get(0));
            elDao.create(eleve);
            JpaUtil.validerTransaction();
            etat = true;
            Message.envoyerMail("rol@moi.com", eleve.getMail(), "Confirmation d'inscription", "L'inscription est un succes");
        } catch (Exception ex) {
            ex.printStackTrace();
            JpaUtil.annulerTransaction();
            Message.envoyerMail("rol@moi.com", eleve.getMail(), "Echec d'inscription", "L'inscription est un echec");
            throw new RuntimeException(ex);
        } finally {
            JpaUtil.fermerContextePersistance();
        }
        return etat;

    }

    public Eleve authentificationEleve(String mail, String mdp) {
        Eleve e = null;
        EleveDao eldao = new EleveDao();
        Boolean loggedIn = false;

        try {
            JpaUtil.creerContextePersistance();
            if (eldao.findByMail(mail).size() > 0) {
                e = eldao.findByMail(mail).get(0);
                if (e.getMotDePasse().equals(mdp)) {
                    loggedIn = true;
                } else {
                    loggedIn = false;
                }
            } else {
                loggedIn = false;
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        } finally {
            JpaUtil.fermerContextePersistance();
        }

        if (loggedIn.equals(false)) {
            e = null;
        }
        return e;
    }

    public Intervenant authentificationIntervenant(String mail, String mdp) {
        Intervenant i = null;
        IntervenantDao idao = new IntervenantDao();
        Boolean loggedIn = false;

        try {
            JpaUtil.creerContextePersistance();
            if (idao.findByMail(mail).size() > 0) {
                i = idao.findByMail(mail).get(0);
                if (i.getMotDePasse().equals(mdp)) {
                    loggedIn = true;
                } else {
                    loggedIn = false;
                }
            } else {
                loggedIn = false;
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        } finally {
            JpaUtil.fermerContextePersistance();
        }

        if (loggedIn.equals(false)) {
            i = null;
        }
        return i;
    }

    public Niveau trouverNiveau(Long id) {
        Niveau n = null;
        NiveauDao nivdao = new NiveauDao();

        try {
            JpaUtil.creerContextePersistance();
            n = nivdao.findById(id);
        } catch (Exception ex) {
            ex.printStackTrace();
        } finally {
            JpaUtil.fermerContextePersistance();
        }

        return n;
    }

    public boolean initialiserNiveau() {
        NiveauDao nvDao = new NiveauDao();
        boolean etat = false;
        Niveau n1 = new Niveau("6ème");
        Niveau n2 = new Niveau("5ème");
        Niveau n3 = new Niveau("4ème");
        Niveau n4 = new Niveau("3ème");
        Niveau n5 = new Niveau("2nde");
        Niveau n6 = new Niveau("1ère");
        Niveau n7 = new Niveau("Terminale");

        try {
            JpaUtil.creerContextePersistance();
            JpaUtil.ouvrirTransaction();
            nvDao.create(n1);
            nvDao.create(n2);
            nvDao.create(n3);
            nvDao.create(n4);
            nvDao.create(n5);
            nvDao.create(n6);
            nvDao.create(n7);
            JpaUtil.validerTransaction();
            etat = true;
        } catch (Exception ex) {
            ex.printStackTrace();
            JpaUtil.annulerTransaction();

        } finally {
            JpaUtil.fermerContextePersistance();
        }
        return etat;
    }

    public List<Niveau> tousNiveau() {
        List<Niveau> n = null;
        NiveauDao nivdao = new NiveauDao();

        try {
            JpaUtil.creerContextePersistance();
            n = nivdao.findAll();
        } catch (Exception ex) {
            ex.printStackTrace();
        } finally {
            JpaUtil.fermerContextePersistance();
        }

        return n;
    }

    public boolean initialiserMatiere() {
        MatiereDao matDao = new MatiereDao();
        boolean etat = false;
        Matiere m1 = new Matiere("Français");
        Matiere m2 = new Matiere("Mathematiques");
        Matiere m3 = new Matiere("Histoire");
        Matiere m4 = new Matiere("Géographie");
        Matiere m5 = new Matiere("SVT");
        Matiere m6 = new Matiere("Philosophie");
        Matiere m7 = new Matiere("Anglais");
        Matiere m8 = new Matiere("Espagnol");
        Matiere m9 = new Matiere("Allemand");
        Matiere m10 = new Matiere("Italien");
        try {
            JpaUtil.creerContextePersistance();
            JpaUtil.ouvrirTransaction();
            matDao.create(m1);
            matDao.create(m2);
            matDao.create(m3);
            matDao.create(m4);
            matDao.create(m5);
            matDao.create(m6);
            matDao.create(m7);
            matDao.create(m8);
            matDao.create(m9);
            matDao.create(m10);

            JpaUtil.validerTransaction();
            etat = true;
        } catch (Exception ex) {
            ex.printStackTrace();
            JpaUtil.annulerTransaction();

        } finally {
            JpaUtil.fermerContextePersistance();
        }
        return etat;
    }

    public Matiere trouverMatiere(Long id) {
        Matiere n = null;
        MatiereDao mdao = new MatiereDao();

        try {
            JpaUtil.creerContextePersistance();
            n = mdao.findById(id);
        } catch (Exception ex) {
            ex.printStackTrace();
        } finally {
            JpaUtil.fermerContextePersistance();
        }

        return n;
    }

    public List<Matiere> toutesMatiere() {
        List<Matiere> n = null;
        MatiereDao mdao = new MatiereDao();

        try {
            JpaUtil.creerContextePersistance();
            n = mdao.findAll();
        } catch (Exception ex) {
            ex.printStackTrace();
        } finally {
            JpaUtil.fermerContextePersistance();
        }

        return n;
    }

    public boolean noterUnCours(Cours c, int note) {
        CoursDao cDao = new CoursDao();

        boolean etat = false;
        try {
            JpaUtil.creerContextePersistance();

            JpaUtil.ouvrirTransaction();

            cDao.setNote(c, note);
            JpaUtil.validerTransaction();
            etat = true;

        } catch (Exception ex) {
            ex.printStackTrace();
            JpaUtil.annulerTransaction();

        } finally {
            JpaUtil.fermerContextePersistance();
        }
        return etat;

    }

    public List<Intervenant> tousIntervenants() {
        List<Intervenant> n = null;
        IntervenantDao idao = new IntervenantDao();

        try {
            JpaUtil.creerContextePersistance();
            n = idao.findAll();
        } catch (Exception ex) {
            ex.printStackTrace();
        } finally {
            JpaUtil.fermerContextePersistance();
        }

        return n;
    }

    public List<Eleve> tousEleve() {
        List<Eleve> n = null;
        EleveDao edao = new EleveDao();

        try {
            JpaUtil.creerContextePersistance();
            n = edao.findAll();
        } catch (Exception ex) {
            ex.printStackTrace();
        } finally {
            JpaUtil.fermerContextePersistance();
        }

        return n;
    }

    public Intervenant trouverIntervenantParId(Long id) {
        Intervenant i = null;
        IntervenantDao idao = new IntervenantDao();

        try {
            JpaUtil.creerContextePersistance();
            i = idao.findById(id);
        } catch (Exception ex) {
            ex.printStackTrace();
        } finally {
            JpaUtil.fermerContextePersistance();
        }

        return i;

    }
}
