package views;

import com.google.gson.*;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;
import metiers.Etablissement;

public class StatsSerialisation extends Serialisation{
    @Override
    public void serialize(HttpServletRequest request, HttpServletResponse response) throws IOException {
        JsonObject container = new JsonObject();
        JsonArray etablissementsArray = new JsonArray();
        JsonArray lowIpsEtablissementArray = new JsonArray();

        Gson gson = new GsonBuilder().setPrettyPrinting().serializeNulls().create();

        long nbEleve = (long)request.getAttribute("nbEleve");
        long nbCours = (long)request.getAttribute("nbCours");
        long nbDemandes = (long)request.getAttribute("nbDemandes");
        long nbIPS = (long)request.getAttribute("nbIPS");

        List<Etablissement> etabEleves = (List<Etablissement>)request.getAttribute("etabEleves");
        List<Etablissement> lowIps = (List<Etablissement>) request.getAttribute("lowIps");

        container.addProperty("nbEleve", nbEleve);
        container.addProperty("nbCours", nbCours);
        container.addProperty("nbDemandes", nbDemandes);
        container.addProperty("nbIPS", nbIPS);

        for(Etablissement etab : etabEleves){
            JsonObject jsonEtablissement = serializeEtablissement(etab);
            etablissementsArray.add(jsonEtablissement);
        }

        for(Etablissement e : lowIps){
            JsonObject jsonLowIps = serializeEtablissement(e);

            lowIpsEtablissementArray.add(jsonLowIps);
        }

        container.add("etablissements", etablissementsArray);
        container.add("lowIps", lowIpsEtablissementArray);

        PrintWriter out = this.getWriter(response);
        gson.toJson(container, out);
        out.close();
    }

    public static JsonObject serializeEtablissement(Etablissement etablissement){
        JsonObject jsonEtablissement = new JsonObject();

        jsonEtablissement.addProperty("id", etablissement.getId());
        jsonEtablissement.addProperty("code", etablissement.getCodeEtablissement());
        jsonEtablissement.addProperty("nom", etablissement.getNom());
        jsonEtablissement.addProperty("longitude", etablissement.getLongitude());
        jsonEtablissement.addProperty("latitude", etablissement.getLatitude());
        jsonEtablissement.addProperty("ips", etablissement.getIps());

        return jsonEtablissement;
    }
}