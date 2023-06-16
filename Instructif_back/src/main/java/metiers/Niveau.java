/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package metiers;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;

/**
 *
 * @author relmir
 */
@Entity
public class Niveau {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private String nomNiveau;

    public Niveau() {
    }

    public Niveau(String nomNiveau) {
        this.nomNiveau = nomNiveau;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getNomNiveau() {
        return nomNiveau;
    }

    public void setNomNiveau(String nomNiveau) {
        this.nomNiveau = nomNiveau;
    }

    @Override
    public String toString() {
        return "Niveau{" + "id=" + id + ", nomNiveau=" + nomNiveau + '}';
    }
   

   

}
