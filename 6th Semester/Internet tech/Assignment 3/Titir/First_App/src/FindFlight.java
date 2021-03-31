import java.io.IOException;
import java.io.*;
import com.google.gson.Gson;
import java.sql.*;
import java.util.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import Models.*;




/**
 * Servlet implementation class SpecialDealApi
 */

public class FindFlight extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
	
	
    public FindFlight() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		//response.getWriter().append("Served at: ").append(request.getContextPath());
		response.setContentType("application/json");
		PrintWriter out = response.getWriter();
		Connection conn = null;
		try {
		String url = "jdbc:postgresql://localhost:5432/flightdb";
  	  String dbDriver = "org.postgresql.Driver";
  	  Class.forName(dbDriver);
  	  Properties parameters = new Properties();
  	  parameters.put("user", "postgres");
  	  parameters.put("password", "1234");
  	  
  	  conn = DriverManager.getConnection(url, parameters);
  	  if (conn != null) {
  		System.out.println("connected to database");
  		String acity = request.getParameter("acity");
  		String dcity = request.getParameter("dcity");
  		
  		
  		String sql = "select * from flight where acity='" + acity + "' and dcity='" + dcity + "'";
  		System.out.println(sql);
  		Statement st = conn.createStatement();
  		
  		ResultSet rs = st.executeQuery(sql);
  		
  		ArrayList<Flight> flights = new ArrayList<>();
  		
  		while(rs.next()) {
  			Flight f = new Flight();
  			f.convert(rs);
  			flights.add(f);
  		}
  		
  		HashMap<String, ArrayList<Flight>> ret = new HashMap<>();
  		ret.put("flights", flights);
  		
  		String selectedFlightsJson = new Gson().toJson(ret);
  		out.print(selectedFlightsJson);
  		out.flush();
  		st.close();
  		
		  //String sql = "select * from specialdeals inner join flight on flight.flightid = specialdeals.flightid";
		 /* Statement st = conn.createStatement();
		  ArrayList<SpecialDeal> arr = new ArrayList<>();
		  
		  ResultSet rs = st.executeQuery(sql);
		  while(rs.next()) {
			  SpecialDeal sp = new SpecialDeal();
			  sp.convert(rs);
			  arr.add(sp);
			 //HashMap<String, SpecialDeal> ret = new HashMap<>();
			 //ret.push()
			 //String flightsJson = new Gson().toJson(ret);
			 
			 //out.print(flightsJson);
			  //out.flush();
			  //st.close();
		  }
		  String sql2 = "select * from flight";
		  st = conn.createStatement();
		  ArrayList<Flight> flights = new ArrayList<>();
		  rs = st.executeQuery(sql2);
		  
		  while(rs.next()) {
			  Flight f = new Flight();
			  f.convert(rs);
			  flights.add(f);
		  }
		  
		  //HashMap<String, ArrayList<SpecialDeal> > ret  = new HashMap<>();
		  //ret.put("offers", arr);
		  ret.put("flights", flights)
		  jsonObject j = new jsonObject();
		  j.flights = flights;
		  j.deals = arr;
		  String flightsJson = new Gson().toJson(j);
		  
		  out.println(flightsJson);*/
		  out.flush();
		  //st.close();
		  
  	  }
  	  }
		catch(SQLException e) {
			e.printStackTrace();
		}
  	  catch(Exception e) {
  		  System.out.println("Exception occured!");
  	  }finally {
  		  
  	  }
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}

