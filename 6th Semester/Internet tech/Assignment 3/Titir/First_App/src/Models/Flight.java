package Models;

import java.sql.ResultSet;
import java.sql.SQLException;

public class Flight{
	String acity;
	String dcity;
	String atime;
	String dtime;
	String code;
	String company;
	String logourl;
	int id;
	double cost;
	String display() {
		return acity + " " + dcity ; 
	}
	public void convert(ResultSet rs) {
		try {
		code = rs.getString("flightid");
		acity = rs.getString("acity");
		dcity = rs.getString("dcity");
		atime = rs.getString("atime");
		dtime = rs.getString("dtime");
		company = rs.getString("company");
		logourl = rs.getString("logourl");
		acity = rs.getString("acity");
		try {
		id = Integer.parseInt(rs.getString("id"));
		}
		catch(Exception e) {
			id = -1;
		}
		try {
		cost = Double.parseDouble(rs.getString("cost"));
		}
		catch(Exception e) {
			cost = -1;
		}
		}
		catch(SQLException e) {
			e.printStackTrace();
		}
		
	}
}