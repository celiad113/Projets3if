package metiers;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
import javax.persistence.Column;
import javax.persistence.Inheritance;
import javax.persistence.InheritanceType;
import javax.persistence.ManyToMany;
import javax.persistence.OneToMany;
import javax.persistence.OneToOne;
import javax.persistence.Version;

/**
 *
 * @author relmir
 */
@Entity
@Inheritance (strategy = InheritanceType.JOINED)
public class Intervenant implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private String nom;
    private String prenom;
    private boolean estDisponible;
    private String telephonePro;
    @Column(unique = true)
    private String email;
    private String motDePasse;
    @ManyToMany
    private List<Niveau> niveau = new ArrayList<>();
    @OneToMany(mappedBy="intervenant")
    private List<Cours> cours = new ArrayList<>();
    @OneToOne
    private Cours coursActuel;
    @Version
    private Long version;
    protected Intervenant() {
    }

    public Intervenant(String nom, String prenom, String telephonePro, String email, String motDePasse) {
        this.nom = nom;
        this.prenom = prenom;
        this.telephonePro = telephonePro;
        this.email = email;
        this.motDePasse = motDePasse;
        this.coursActuel = null;
        this.estDisponible = true;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getNom() {
        return nom;
    }

    public void setNom(String nom) {
        this.nom = nom;
    }

    public String getPrenom() {
        return prenom;
    }

    public void setPrenom(String prenom) {
        this.prenom = prenom;
    }

    public boolean isEstDisponible() {
        return estDisponible;
    }

    public void setEstDisponible(boolean estDisponible) {
        this.estDisponible = estDisponible;
    }

    public String getTelephonePro() {
        return telephonePro;
    }

    public void setTelephonePro(String telephonePro) {
        this.telephonePro = telephonePro;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getMotDePasse() {
        return motDePasse;
    }

    public void setMotDePasse(String motDePasse) {
        this.motDePasse = motDePasse;
    }

    public List<Niveau> getNiveau() {
        return niveau;
    }

    public void setNiveau(List<Niveau> niveau) {
        this.niveau = niveau;
    }

    public void addNiveauToList(Niveau nv)
    {
        this.niveau.add(nv);
    }
    
    public void addCoursToList(Cours c)
    {
        this.cours.add(c);
        if (c.getIntervenant() != this){
            c.setIntervenant(this);
        }
    }

    public List<Cours> getCours() {
        return cours;
    }

    public void setCours(List<Cours> cours) {
        this.cours = cours;
    }

    public Cours getCoursActuel() {
        return coursActuel;
    }

    public void setCoursActuel(Cours coursActuel) {
        this.coursActuel = coursActuel;
    }

    @Override
    public String toString() {
        return "id=" + id + ", nom=" + nom + ", prenom=" + prenom + ", estDisponible=" + estDisponible + ", telephonePro=" + telephonePro + ", email=" + email + ", motDePasse=" + motDePasse + ", niveau=" + niveau + ", cours=" + cours + ", coursActuel=" + coursActuel;
    }


    
}
