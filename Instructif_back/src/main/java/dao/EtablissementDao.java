/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dao;

import java.util.List;
import javax.persistence.TypedQuery;
import metiers.Eleve;
import metiers.Etablissement;

/**
 *
 * @author relmir
 */
public class EtablissementDao {
     public void create(Etablissement etablissement)
    {
        JpaUtil.obtenirContextePersistance().persist(etablissement);
    }
    
    public Etablissement findById(Long id)
    {
        return JpaUtil.obtenirContextePersistance().find(Etablissement.class, id);
    }
    
    
    public List<Etablissement> findByCode(String code)
    {
        String s = "select e from Etablissement e where e.codeEtablissement = :unCode ";
        TypedQuery query = JpaUtil.obtenirContextePersistance().createQuery(s, Etablissement.class);
        query.setParameter("unCode", code);
        return query.getResultList();
    }
    
    public List<Etablissement> findAll(int state, double ips)
    {
         switch (state) {
             case 1:
             {
                 String s = "select e from Etablissement e where e.ips < :ips ";
                 TypedQuery query = JpaUtil.obtenirContextePersistance().createQuery(s, Etablissement.class);
                 query.setParameter("ips", ips);
                 return query.getResultList();
             }    case 0:
             {
                 String s = "select e from Etablissement e";
                 TypedQuery query = JpaUtil.obtenirContextePersistance().createQuery(s, Etablissement.class);
                 return query.getResultList();
             }    default:
                 return null;
         }
    }
    
    
}
