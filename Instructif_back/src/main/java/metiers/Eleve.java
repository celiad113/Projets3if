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
import java.io.Serializable;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;
import javax.persistence.Column;
import javax.persistence.ManyToOne;
import javax.persistence.OneToMany;
import javax.persistence.OneToOne;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;
/**
 *
 * @author relmir
 */
@Entity
public class Eleve {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private String nom;
    private String prenom;
    @Temporal(TemporalType.DATE)
    private Date dateNaissance;
    @Column(unique = true)
    private String mail;
    private String motDePasse;
    @ManyToOne
    private Niveau niveauScolaire;
    @ManyToOne
    private Etablissement etablissement;
    @OneToMany(mappedBy="eleve")
    private List<Cours> cours;
    @OneToOne
    private Cours coursActuel;

    public Eleve(String nom, String prenom, String dateN, String mail, String motDePasse, Niveau niveauS) throws ParseException {
        this.nom = nom;
        this.prenom = prenom;
        this.dateNaissance = new SimpleDateFormat("yyyy/MM/dd").parse(dateN);
        this.mail = mail;
        this.motDePasse = motDePasse;
        this.niveauScolaire = niveauS;
        this.etablissement = null;
        this.coursActuel = null;
    }
    
    protected Eleve() {
    }

    public Long getId() {
        return id;
    }

    public String getNom() {
        return nom;
    }

    public String getPrenom() {
        return prenom;
    }

    public Date getDateNaissance() {
        return dateNaissance;
    }

    public String getMail() {
        return mail;
    }

    public String getMotDePasse() {
        return motDePasse;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public void setNom(String nom) {
        this.nom = nom;
    }

    public void setPrenom(String prenom) {
        this.prenom = prenom;
    }

    public void setDateNaissance(String dateN) throws ParseException {
        this.dateNaissance = new SimpleDateFormat("yyyy/MM/dd").parse(dateN);
    }


    public void setMail(String mail) {
        this.mail = mail;
    }

    public void setMotDePasse(String motDePasse) {
        this.motDePasse = motDePasse;
    }

    public Niveau getNiveauScolaire() {
        return niveauScolaire;
    }

    public void setNiveauScolaire(Niveau niveauScolaire) {
        this.niveauScolaire = niveauScolaire;
    }

    public Etablissement getEtablissement() {
        return etablissement;
    }

    public void setEtablissement(Etablissement etablissement) {
        this.etablissement = etablissement;
    }

    public List<Cours> getCours() {
        return cours;
    }

    public void setCours(List<Cours> cours) {
        this.cours = cours;
    }
    
    public void addCoursToList(Cours c)
    {
        this.cours.add(c);
        if (c.getEleve() != this){
            c.setEleve(this);
        }
    }

    public Cours getCoursActuel() {
        return coursActuel;
    }

    public void setCoursActuel(Cours coursActuel) {
        this.coursActuel = coursActuel;
    }

    @Override
    public String toString() {
        return "Eleve{" + "id=" + id + ", nom=" + nom + ", prenom=" + prenom + ", dateNaissance=" + dateNaissance + ", mail=" + mail + ", motDePasse=" + motDePasse + ", niveauScolaire=" + niveauScolaire + ", etablissement=" + etablissement + ", cours=" + cours + ", coursActuel=" + coursActuel + '}';
    }
    
    
}
