package views;

import com.google.gson.*;
import metiers.Cours;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.io.PrintWriter;

public class CoursEnAttenteSerialisation extends Serialisation{
    @Override
    public void serialize(HttpServletRequest request, HttpServletResponse response) throws IOException {
        HttpSession session = request.getSession(false);

        Cours coursActuel = (Cours)session.getAttribute("coursActuel");
        JsonObject container = new JsonObject();

        if(coursActuel != null){
            container.addProperty("id", coursActuel.getId());

            JsonObject jsonEleve = new JsonObject();

            // Adding the student property
            jsonEleve.addProperty("prenom", coursActuel.getEleve().getPrenom());
            jsonEleve.addProperty("nom", coursActuel.getEleve().getNom());
            jsonEleve.addProperty("niveau", coursActuel.getEleve().getNiveauScolaire().getNomNiveau());
            jsonEleve.addProperty("etablissement", coursActuel.getEleve().getEtablissement().getNom());

            container.add("eleve", jsonEleve);

            container.addProperty("matiere", coursActuel.getMatiere().getNomMatiere());
            container.addProperty("commentaire", coursActuel.getCommentaire());
        }

        System.out.println(container);

        Gson gson = new GsonBuilder().serializeNulls().setPrettyPrinting().create();
        PrintWriter out = response.getWriter();

        gson.toJson(container, out);
    }
}
