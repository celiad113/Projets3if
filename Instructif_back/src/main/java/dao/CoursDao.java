/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dao;

import java.util.List;
import javax.persistence.TypedQuery;
import metiers.Cours;

/**
 *
 * @author spignol
 */
public class CoursDao {
     public void create(Cours cours)
    {
        JpaUtil.obtenirContextePersistance().persist(cours);
    }
    
    public Cours findById(Long id)
    {
       
        return JpaUtil.obtenirContextePersistance().find(Cours.class, id);
        
    }
    
    
    public List<Cours> findAll()
    {
        String s = "select e from Cours e";
        TypedQuery query = JpaUtil.obtenirContextePersistance().createQuery(s, Cours.class);
        return query.getResultList();
    }
    public void setNote(Cours c, int i)
    {
           c.setNote(i);
           JpaUtil.obtenirContextePersistance().merge(c);
      
    }
    
    public List<Long> count()
    {        
        String s = "select count(e) from Cours e";
        TypedQuery query = JpaUtil.obtenirContextePersistance().createQuery(s, Cours.class);
        return query.getResultList();

    }
     
        public List<Long> countToday()
    {        
        String s = "select count(e) from Cours e where e.date = CURRENT_DATE";
        TypedQuery query = JpaUtil.obtenirContextePersistance().createQuery(s, Cours.class);
        return query.getResultList();

    }
    
}
