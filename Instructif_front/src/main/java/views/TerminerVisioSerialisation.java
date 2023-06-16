package views;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonObject;
import metiers.Cours;
import views.Serialisation;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.io.PrintWriter;

public class TerminerVisioSerialisation extends Serialisation {
    @Override
    public void serialize(HttpServletRequest request, HttpServletResponse response) throws IOException {
        HttpSession session = request.getSession();
        JsonObject container = new JsonObject();
        Cours cours = (Cours) session.getAttribute("cours");
        if (cours != null) {
            PrintWriter out = this.getWriter(response);
            Gson gson = new GsonBuilder().setPrettyPrinting().serializeNulls().create();
            gson.toJson(container, out);
            out.close();
        }
    }
}
