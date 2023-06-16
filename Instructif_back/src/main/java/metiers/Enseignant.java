/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package metiers;

import javax.persistence.Entity;

/**
 *
 * @author relmir
 */
@Entity
public class Enseignant extends Intervenant{
    private String typeEtablissement;

    public Enseignant(String nom, String prenom, String telephonePro, String email, String motDePasse, String typeEtablissement) {
        super(nom, prenom,telephonePro, email, motDePasse);
        this.typeEtablissement = typeEtablissement;
    }

    public Enseignant() {
    }
    
    

    public String getTypeEtablissement() {
        return typeEtablissement;
    }

    public void setTypeEtablissement(String typeEtablissement) {
        this.typeEtablissement = typeEtablissement;
    }

    @Override
    public String toString() {
        return "Enseignant{" + super.toString() + " , " + "typeEtablissement=" + typeEtablissement + '}';
    }
    
    
}
