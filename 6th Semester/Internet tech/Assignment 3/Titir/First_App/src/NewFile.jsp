<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ import="java.import.sql.*" %> 
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<body>
	Hello
	This is Titir 
	
	<%
	String url = "jdbc:postgresql://localhost:5432/flightdb"
	String username = "postgres";
	String password = "1234";
	String sql = "select * from flight where id=0";
	Class.forName("org.postgresql.Driver");
	Connection con = DriverManager.getConnection(url, username, password);
	Statement st = con.createStatement();
	
	ResultSet rs = st.executeQuery(sql);
	rs.next();
	
	
	
	%>
	
	 
</body>
</html>