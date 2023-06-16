package views;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonObject;
import metiers.Eleve;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.io.PrintWriter;
import java.text.SimpleDateFormat;
import java.util.Date;

public class EspaceEleveSerialisation extends Serialisation{
    @Override
    public void serialize(HttpServletRequest request, HttpServletResponse response) throws IOException {
        HttpSession session = request.getSession();

        JsonObject container = new JsonObject();

        Eleve eleve = (Eleve)session.getAttribute("eleve");

        JsonObject jsonEleve = serializeEleve(eleve);

        container.add("eleve", jsonEleve);

        Gson gson = new GsonBuilder().serializeNulls().setPrettyPrinting().create();

        PrintWriter out = response.getWriter();
        gson.toJson(container,out);
    }

    public static JsonObject serializeEleve(Eleve eleve){
        JsonObject jsonEleve = new JsonObject();

        jsonEleve.addProperty("id",eleve.getId());
        jsonEleve.addProperty("prenom",eleve.getPrenom());
        jsonEleve.addProperty("nom",eleve.getNom());
        jsonEleve.addProperty("niveau", eleve.getNiveauScolaire().getNomNiveau());

        JsonObject jsonCours = new JsonObject();

        if(eleve.getCoursActuel() != null){
            jsonCours.addProperty("id", eleve.getCoursActuel().getId());

            JsonObject jsonMatiere = new JsonObject();
            jsonMatiere.addProperty("id", eleve.getCoursActuel().getMatiere().getId());
            jsonMatiere.addProperty("nom", eleve.getCoursActuel().getMatiere().getNomMatiere());
            jsonCours.add("matiere", jsonMatiere);

            JsonObject jsonIntervenant = new JsonObject();
            jsonIntervenant.addProperty("id", eleve.getCoursActuel().getIntervenant().getId());
            jsonIntervenant.addProperty("prenom", eleve.getCoursActuel().getIntervenant().getPrenom());
            jsonIntervenant.addProperty("nom", eleve.getCoursActuel().getIntervenant().getNom());

            jsonCours.addProperty("message", eleve.getCoursActuel().getCommentaire());
            jsonCours.add("intervenant", jsonIntervenant);
        }

        jsonEleve.add("cours", jsonCours);

        return jsonEleve;
    }


}
