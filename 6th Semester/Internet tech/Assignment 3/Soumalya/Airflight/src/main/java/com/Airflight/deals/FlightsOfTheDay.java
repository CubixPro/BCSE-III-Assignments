package com.Airflight.deals;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;


import java.util.*;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;



class Flight
{
	private String sourceCity, destCity, carrier, journeyDate, journeyTime;
	private int cost, legs, id;
	
	// needed date, start time and endtime attributes
	
	//	private int dd, mm, yy, deptTime; // start and end are in minutes from midnight 
	
	public Flight() {}
	public Flight(int id, String sourceCity, String destCity, int cost, String time, int legs, String journeyDate, String journeyTime, String carrier)
	{
		
		this.id				= id;
		this.sourceCity 	= sourceCity;
		this.destCity		= destCity;
		this.cost 			= cost;
//		this.time			= time;
		this.legs			= legs;
		this.journeyDate	= journeyDate;
		this.journeyTime	= journeyTime;
		this.carrier		= carrier;
		
	}
	
	public void convert(ResultSet rs)
	{
		try {
			this.id 			= Integer.parseInt(rs.getString("id"));
			this.sourceCity 	= rs.getString("source");
			this.destCity		= rs.getString("dest");
			this.cost 			= Integer.parseInt(rs.getString("cost"));
			this.legs			= Integer.parseInt(rs.getString("legs"));
			this.journeyDate	= rs.getString("journeyDate");
			this.journeyTime	= rs.getString("journeyTime");
			this.carrier 		= rs.getString("carrier");
		} catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
		}
	}
}

//
//class FlightList
//{
//	private ArrayList<Flight> arrayList;
//	
//	public FlightList()
//	{
//		this.arrayList = new ArrayList<>();
//	}
//	
//	public void addFlighttoList(String source, String dest, int cost, int time, int legs, String company, int dd, int mm, int yy, int dept)
//	{
//		Flight newFlight = new Flight(source, dest, cost, time, legs, company, dd, mm, yy, dept);
//		arrayList.add(newFlight);
//	}
//	
//	public ArrayList<Flight> getFlightList()
//	{
//		return this.arrayList;
//	}
//}




@WebServlet("/flights")
public class FlightsOfTheDay extends HttpServlet{
	/**
	 * 
	 */
	
	private static final long serialVersionUID = 1L;

	protected void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException
	{
		res.setContentType("application/json");
		
		ArrayList<Flight> flightList = new ArrayList<>();
		Connection connection = null;
		
		try {
			
			Class.forName("org.postgresql.Driver");
			connection = DriverManager.getConnection("jdbc:postgresql://localhost:5432/FlightDB", "postgres", "soumalya@10");
			
			if(connection != null)
				System.out.println("Hey hello high yoo");
			else 
				System.out.println("Nopeeeeeeeeeeeeeeee!");
			
		} catch (Exception e) {
			// TODO: handle exception
			System.out.println(e);
		}
		
		//System.out.println("Here inside of flights");
		String query = "select * from \"Flights\"";
		

		
		
		try {
			Statement st= connection.createStatement();
			ResultSet rs = st.executeQuery(query);
			
			while(rs.next()) {
	  			Flight flight = new Flight();
	  			flight.convert(rs);
	  			flightList.add(flight);
	  			//System.out.println("BoomBaamBoomBaam");
	  		}
			
			st.close();
			//connection.close();
			
		} catch (SQLException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		
		

		
		PrintWriter out = res.getWriter();
		

		
		GsonBuilder gsonBuilder = new GsonBuilder().setPrettyPrinting();
		Gson gson = gsonBuilder.create();
		String jsonObj = gson.toJson(flightList);
		out.print(jsonObj);

	}
}



















