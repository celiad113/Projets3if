package views;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import metiers.Cours;
import metiers.Matiere;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

public class DemanderCoursSerialisation extends Serialisation{

    @Override
    public void serialize(HttpServletRequest request, HttpServletResponse response) throws IOException {

        HttpSession session = request.getSession();
        JsonObject container = new JsonObject();

        Cours cours = (Cours) session.getAttribute("cours");

        if (cours != null) {
            JsonObject coursObj = new JsonObject();
            coursObj.addProperty( "id", cours.getId());

            JsonObject matiereObj = new JsonObject();
            matiereObj.addProperty("id", cours.getMatiere().getId());
            matiereObj.addProperty("nomMatiere", cours.getMatiere().getNomMatiere());
            coursObj.add("matiere",matiereObj);

            JsonObject eleveObj = new JsonObject();
            eleveObj.addProperty("prenom", cours.getEleve().getPrenom());
            eleveObj.addProperty("cours_actuel", cours.getEleve().getCoursActuel().getId());
            coursObj.add("eleve", eleveObj);
            coursObj.addProperty("date", cours.getDate().toString());
            coursObj.addProperty("commentaire", cours.getCommentaire());
            coursObj.addProperty("note", cours.getNote());

            JsonObject intervenantObj = new JsonObject();
            intervenantObj.addProperty("nom", cours.getIntervenant().getNom());
            intervenantObj.addProperty("prenom", cours.getIntervenant().getPrenom());
            coursObj.add("intervenant", intervenantObj);

            container.add("cours", coursObj);
        }

        PrintWriter out = this.getWriter(response);
        Gson gson = new GsonBuilder().setPrettyPrinting().serializeNulls().create();
        gson.toJson(container, out);
        System.out.println(container);
        out.close();
    }
}
