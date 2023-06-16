package views;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import metiers.Niveau;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

public class NiveauxSerialisation extends Serialisation{
    @Override
    public void serialize(HttpServletRequest request, HttpServletResponse response) throws IOException {
        HttpSession session = request.getSession(false);

        List<Niveau> niveaux = (List<Niveau>) session.getAttribute("niveaux");

        JsonObject container = new JsonObject();
        JsonArray niveauxArray = new JsonArray();

        for(Niveau n : niveaux){
            JsonObject jsonNiveau = new JsonObject();

            jsonNiveau.addProperty("id", n.getId());
            jsonNiveau.addProperty("nom", n.getNomNiveau());

            niveauxArray.add(jsonNiveau);
        }

        container.add("niveaux", niveauxArray);

        PrintWriter out = response.getWriter();
        Gson gson = new GsonBuilder().serializeNulls().setPrettyPrinting().create();
        gson.toJson(container,out);
    }
}
