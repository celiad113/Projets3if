package views;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonObject;
import metiers.Eleve;
import views.Serialisation;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.io.PrintWriter;
import java.text.SimpleDateFormat;
import java.util.Date;

public class ProfilEleveSerialisation extends Serialisation {
    @Override
    public void serialize(HttpServletRequest request, HttpServletResponse response) throws IOException {
        JsonObject container = new JsonObject();
        HttpSession session = request.getSession(false);

        Eleve eleve = (Eleve)session.getAttribute("eleve");
        JsonObject jsonEleve = new JsonObject();
        boolean success = false;

        if(eleve != null){
            success = true;
            jsonEleve.addProperty("id",eleve.getId());
            jsonEleve.addProperty("prenom",eleve.getPrenom());
            jsonEleve.addProperty("nom",eleve.getNom());
            jsonEleve.addProperty("username",eleve.getMail());
            jsonEleve.addProperty("dateNaissance", formatDate(eleve.getDateNaissance(), "dd/MM/yyyy"));

            JsonObject jsonEtablissement = new JsonObject();
            jsonEtablissement.addProperty("code",eleve.getEtablissement().getCodeEtablissement());
            jsonEtablissement.addProperty("nom",eleve.getEtablissement().getNom());
            jsonEtablissement.addProperty("commune",eleve.getEtablissement().getCommune());
            jsonEleve.add("etablissement",jsonEtablissement);

            JsonObject jsonNiveau = new JsonObject();
            jsonNiveau.addProperty("id", eleve.getNiveauScolaire().getId());
            jsonNiveau.addProperty("nom", eleve.getNiveauScolaire().getNomNiveau());
            jsonEleve.add("niveau", jsonNiveau);
        }

        String operation = (String)session.getAttribute("operation");
        container.addProperty(operation, success);

        container.add("eleve",jsonEleve);

        System.out.println(container);

        PrintWriter out = this.getWriter(response);
        Gson gson = new GsonBuilder().setPrettyPrinting().serializeNulls().create();

        gson.toJson(container, out);
        out.close();
    }

    public static String formatDate(Date date, String format){
        SimpleDateFormat inputFormat = new SimpleDateFormat(format);

        return inputFormat.format(date);
    }

}
