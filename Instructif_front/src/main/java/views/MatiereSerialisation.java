package views;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import metiers.Etablissement;
import metiers.Matiere;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

public class MatiereSerialisation extends Serialisation{
    @Override
    public void serialize(HttpServletRequest request, HttpServletResponse response) throws IOException {
        JsonObject container = new JsonObject();

        List<Matiere> matieres = (List<Matiere>) request.getAttribute("matieres");

        JsonArray matieresArray = new JsonArray();
        for (Matiere matiere : matieres) {
            JsonObject matiereObj = new JsonObject();
            matiereObj.addProperty("id", matiere.getId());
            matiereObj.addProperty("nom", matiere.getNomMatiere());
            matieresArray.add(matiereObj);
        }
        container.add("matieres", matieresArray);
        System.out.println(container);
        PrintWriter out = this.getWriter(response);
        Gson gson = new GsonBuilder().setPrettyPrinting().serializeNulls().create();
        gson.toJson(container, out);
        out.close();
    }
}
