/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dao;

import java.text.ParseException;
import java.util.ArrayList;
import java.util.List;
import javax.persistence.TypedQuery;
import metiers.Cours;
import metiers.Eleve;
import metiers.Etablissement;
import metiers.Niveau;

/**
 *
 * @author relmir
 */
public class EleveDao {
     public void create(Eleve eleve)
    {
        JpaUtil.obtenirContextePersistance().persist(eleve);
    }
    
    public Eleve findById(Long id)
    {
        return JpaUtil.obtenirContextePersistance().find(Eleve.class, id);
    }
    
    public List<Eleve> findByMail(String email)
    {
        String s = "select e from Eleve e where e.mail = :unEmail ";
        TypedQuery<Eleve> query = JpaUtil.obtenirContextePersistance().createQuery(s, Eleve.class);
        query.setParameter("unEmail", email);
        return query.getResultList();
    }
    
    public List<Eleve> findAll()
    {
        String s = "select e from Eleve e";
        TypedQuery<Eleve> query = JpaUtil.obtenirContextePersistance().createQuery(s, Eleve.class);
        return query.getResultList();
    }
    
    public void addCoursToListEleve(Eleve e, Cours c)
    {
        e.addCoursToList(c);
        JpaUtil.obtenirContextePersistance().merge(e);
    }
    
    public void updateCoursActuel(Eleve e, Cours c)
    {
        e.setCoursActuel(c);
        JpaUtil.obtenirContextePersistance().merge(e);
    }
    
    public List<Long> count(int state, double ips)
    {        
         switch (state) {
             case 0:
             {
                 String s = "select count(e) from Eleve e";
                 TypedQuery query = JpaUtil.obtenirContextePersistance().createQuery(s, Eleve.class);
                 return query.getResultList();
             }    case 1:
             {
                 String s = "select count(e) from Eleve e where e.etablissement.ips < :ips";
                 TypedQuery query = JpaUtil.obtenirContextePersistance().createQuery(s, Eleve.class);
                 query.setParameter("ips", ips);
                 return query.getResultList();
             }    default:
                 List<Long> c = new ArrayList();
                 c.add(-1l);
                 return c;
         }
            
    }
    
    public void updateEleve(Eleve eleve, String nom, String prenom, String dateN, String mail, Niveau niveau, Etablissement etab) throws ParseException
    {
        eleve.setNom(nom);
        eleve.setPrenom(prenom);
        eleve.setDateNaissance(dateN);
        eleve.setMail(mail);
        eleve.setNiveauScolaire(niveau);
        eleve.setEtablissement(etab);
        JpaUtil.obtenirContextePersistance().merge(eleve);
    }
}
