/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package metiers;


import java.io.Serializable;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

/**
 *
 * @author relmir
 */
@Entity
public class Etablissement implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    @Column(unique = true)
    private String codeEtablissement;
    private Double ips;
    private String nom;
    private Double latitude;
    private Double longitude;
    private String commune;

    public Etablissement() {
    }

    public Etablissement(String codeEtablissement, double ips, String nom, String commune, Double lng, Double lat) {
        this.codeEtablissement = codeEtablissement;
        this.ips = ips;
        this.nom = nom;
        this.commune = commune;
        this.longitude = lng;
        this.latitude = lat;
    }

    public String getCodeEtablissement() {
        return codeEtablissement;
    }

    public void setCodeEtablissement(String codeEtablissement) {
        this.codeEtablissement = codeEtablissement;
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public double getIps() {
        return ips;
    }

    public void setIps(double ips) {
        this.ips = ips;
    }

    public String getNom() {
        return nom;
    }

    public void setNom(String nom) {
        this.nom = nom;
    }

    public String getCommune() {
        return commune;
    }

    public void setCommune(String commune) {
        this.commune = commune;
    }

    public double getLatitude() {
        return latitude;
    }

    public void setLatitude(double latitude) {
        this.latitude = latitude;
    }

    public double getLongitude() {
        return longitude;
    }

    public void setLongitude(double longitude) {
        this.longitude = longitude;
    }

    @Override
    public String toString() {
        return "Etablissement{" + "id=" + id + ", codeEtablissement=" + codeEtablissement + ", ips=" + ips + ", nom=" + nom + ", latitude=" + latitude + ", longitude=" + longitude + ", commune=" + commune + '}';
    }


}
