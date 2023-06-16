package views;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

public abstract class Serialisation {
    public abstract void serialize(HttpServletRequest request, HttpServletResponse response) throws IOException;

    public PrintWriter getWriter(HttpServletResponse response) throws IOException {
        response.setContentType("application/json;charset = UTF-8");
        return response.getWriter();
    }
}
