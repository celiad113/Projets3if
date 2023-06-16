/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dao;

import java.util.List;
import javax.persistence.TypedQuery;
import metiers.Cours;
import metiers.Intervenant;
import metiers.Niveau;

/**
 *
 * @author relmir
 */
public class IntervenantDao {

    public IntervenantDao() {
    }
    
    
    
    public void create(Intervenant employe)
    {
        JpaUtil.obtenirContextePersistance().persist(employe);
    }
    
    public Intervenant findById(Long id)
    {
        return JpaUtil.obtenirContextePersistance().find(Intervenant.class, id);
    }
    
    public List<Intervenant> findAll()
    {
        String s = "select e from Intervenant e";
        TypedQuery query = JpaUtil.obtenirContextePersistance().createQuery(s, Intervenant.class);
        return query.getResultList();
    }
    
    public void addCoursToListIntervenant(Intervenant i, Cours c)
    {
        i.addCoursToList(c);
        JpaUtil.obtenirContextePersistance().merge(i);
    }

    public List<Intervenant> findByNiveau(Niveau niveau)
    {
        String s = "select i from Intervenant i where :niveau member of i.niveau and i.estDisponible = true order by size(i.cours)";
        TypedQuery query = JpaUtil.obtenirContextePersistance().createQuery(s, Intervenant.class);
        query.setParameter("niveau", niveau);
        return query.getResultList();
    }
    
    public void updateCoursActuelEtDisponibilite(Intervenant i, Cours c, boolean dispo)
    {
        i.setCoursActuel(c);
        i.setEstDisponible(dispo);
        JpaUtil.obtenirContextePersistance().merge(i);
    }
    
    public List<Intervenant> findByMail(String email)
    {
        String s = "select e from Intervenant e where e.email = :unEmail ";
        TypedQuery query = JpaUtil.obtenirContextePersistance().createQuery(s, Intervenant.class);
        query.setParameter("unEmail", email);
        return query.getResultList();
    }
}
