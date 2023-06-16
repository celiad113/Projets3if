/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dao;

import java.util.List;
import javax.persistence.TypedQuery;
import metiers.Niveau;

/**
 *
 * @author relmir
 */
public class NiveauDao {
     public void create(Niveau niveau)
    {
        JpaUtil.obtenirContextePersistance().persist(niveau);
    }
    
    public Niveau findById(Long id)
    {
        return JpaUtil.obtenirContextePersistance().find(Niveau.class, id);
    }
    
    
    public List<Niveau> findAll()
    {
        String s = "select e from Niveau e order by e.id";
        TypedQuery<Niveau> query = JpaUtil.obtenirContextePersistance().createQuery(s, Niveau.class);
        return query.getResultList();
    }
    
}
