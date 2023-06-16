package views;

import com.google.gson.*;
import metiers.Autre;
import metiers.Eleve;
import metiers.Intervenant;
import metiers.Niveau;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Objects;

public class ProfilEnseignantSerialisation extends Serialisation{
    @Override
    public void serialize(HttpServletRequest request, HttpServletResponse response) throws IOException {
        HttpSession session = request.getSession(false);

        Gson gson = new GsonBuilder().setPrettyPrinting().serializeNulls().create();
        JsonObject container = new JsonObject();

        Intervenant intervenant = (Intervenant) session.getAttribute("intervenant");

        boolean success = !(intervenant == null);

        container.addProperty("connexion", success);

        if(intervenant != null){
            JsonObject intervenantJson = new JsonObject();
            intervenantJson.addProperty("id", intervenant.getId());
            intervenantJson.addProperty("prenom", intervenant.getPrenom());
            intervenantJson.addProperty("nom", intervenant.getNom());
            intervenantJson.addProperty("email", intervenant.getEmail());
            intervenantJson.addProperty("telephone", intervenant.getTelephonePro());
            intervenantJson.addProperty("estDisponible", intervenant.isEstDisponible());

            JsonArray niveauArray = new JsonArray();

            for(Niveau n : intervenant.getNiveau()){
                JsonObject niveauJson = new JsonObject();

                niveauJson.addProperty("id", n.getId());
                niveauJson.addProperty("nom", n.getNomNiveau());

                niveauArray.add(niveauJson);
            }

            intervenantJson.add("niveaux", niveauArray);

            if(intervenant instanceof Autre){
                intervenant = (Autre)intervenant;
                intervenantJson.addProperty("activite", ((Autre) intervenant).getActivite());
            }
            else{
                intervenantJson.addProperty("activite", intervenant.getClass().getName());
            }

            container.add("intervenant", intervenantJson);
        }


        // On ecrit sur le flux de sortie
        PrintWriter out = this.getWriter(response);
        gson.toJson(container, out);

        System.out.println(container);
    }
}
