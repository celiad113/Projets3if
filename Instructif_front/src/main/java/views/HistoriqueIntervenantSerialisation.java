package views;

import com.google.gson.*;
import metiers.Cours;
import metiers.Intervenant;

import java.io.PrintWriter;
import java.text.SimpleDateFormat;
import java.util.Date;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.util.List;

public class HistoriqueIntervenantSerialisation extends Serialisation{
    @Override
    public void serialize(HttpServletRequest request, HttpServletResponse response) throws IOException {
        HttpSession session = request.getSession(false);

        Intervenant intervenant = (Intervenant) session.getAttribute("intervenant");

        List<Cours> historiqueCours = intervenant.getCours();

        if(historiqueCours.isEmpty()) return;

        JsonObject container = new JsonObject();

        JsonArray historiqueJson = new JsonArray(historiqueCours.size());

        for( Cours c : historiqueCours ){
            JsonObject coursJson = new JsonObject();

            coursJson.addProperty("id", c.getId());
            coursJson.addProperty("date", dateToString(c.getDate()));
            coursJson.addProperty("note", c.getNote());

            JsonObject jsonEleve = new JsonObject();
            jsonEleve.addProperty("id", c.getEleve().getId());
            jsonEleve.addProperty("prenom", c.getEleve().getPrenom());
            jsonEleve.addProperty("nom", c.getEleve().getNom());

            coursJson.add("eleve",jsonEleve);

            JsonObject jsonMatiere = new JsonObject();
            jsonMatiere.addProperty("id", c.getMatiere().getId());
            jsonMatiere.addProperty("nomMatiere", c.getMatiere().getNomMatiere());

            coursJson.add("matiere", jsonMatiere);

            historiqueJson.add(coursJson);
        }

        container.add("historique", historiqueJson);

        PrintWriter out = response.getWriter();

        Gson gson = new GsonBuilder().serializeNulls().setPrettyPrinting().create();
        gson.toJson(container,out);
    }

    public static String dateToString(Date date) {
        SimpleDateFormat formatter = new SimpleDateFormat("dd/MM/yyyy");
        return formatter.format(date);
    }
}
