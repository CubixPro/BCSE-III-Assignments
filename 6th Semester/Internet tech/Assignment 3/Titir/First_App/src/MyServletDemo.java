import java.io.*;

import java.sql.*;
import java.util.Properties;

import javax.servlet.*;
import javax.servlet.http.*;



// Extend HttpServlet class to create Http Servlet
public class MyServletDemo extends HttpServlet {

   private String mymsg;
   
   public void doPost(HttpServletRequest request, HttpServletResponse response) 
   throws ServletException, IOException{
	   int num1 = Integer.parseInt(request.getParameter("name1"));
	   int num2 = Integer.parseInt(request.getParameter("name2"));
	   int k  = num1 + num2;
	   System.out.println("Result is " + k);
	   response.setContentType("text/html");

	      // Writing message to the web page
	      PrintWriter out = response.getWriter();
	      out.println("<h1>" + mymsg + k + "</h1>");
   }

   public void init() throws ServletException {
      mymsg = "Hello World!";
   }

   public void doGet(HttpServletRequest request, 
      HttpServletResponse response)
      throws ServletException, IOException
   {

	   int num1 = Integer.parseInt(request.getParameter("name1"));
	   int num2 = Integer.parseInt(request.getParameter("name2"));
	   int k  = num1 + num2;
      // Setting up the content type of webpage
      response.setContentType("text/html");

      // Writing message to the web page
      PrintWriter out = response.getWriter();
      out.println("<h1>" +  k + "</h1>");
      
      //check database
      
      Connection conn = null;
      try {
    	  String url = "jdbc:postgresql://localhost:5432/flightdb";
    	  String dbDriver = "org.postgresql.Driver";
    	  Class.forName(dbDriver);
    	  Properties parameters = new Properties();
    	  parameters.put("user", "postgres");
    	  parameters.put("password", "1234");
    	  
    	  conn = DriverManager.getConnection(url, parameters);
    	  if(conn != null) {
    		  System.out.println("connected to database");
    		  String sql = "select * from flight where id=0";
    		  Statement st = conn.createStatement();
    		  ResultSet rs = st.executeQuery(sql);
    		  rs.next();
    		  out.println(rs.getString("code"));
    	  }
    	  else {
    		  System.out.println("Couldn't connect");
    	  }
      }catch(SQLException ex) {
    	  System.out.println("Ran into some error");
    	  ex.printStackTrace();
      }
      catch(Exception exp) {
    	  System.out.println("Some exception");
      }
      finally {
    	  //System.out.println("Ran into some error");
      }
      
      
   }

   public void destroy() {
      /* leaving empty for now this can be
       * used when we want to do something at the end
       * of Servlet life cycle
       */
   }
}
