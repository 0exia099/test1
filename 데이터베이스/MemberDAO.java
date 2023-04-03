package member;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.LinkedList;
import java.util.List;

public class MemberDAO {
	private Connection conn;
	private PreparedStatement query;
	private Statement stmt;

	private final String url = "jdbc:oracle:thin:@localhost:1521/xepdb1";
	private final String dbId = "scott";
	private final String dbPw = "tiger";

	public MemberDAO() {
		conn = null;
		query = null;
		stmt = null;
		try {
			Class.forName("oracle.jdbc.driver.OracleDriver");
		} catch (ClassNotFoundException e) {
			System.err.println("ClassNotFoundException : " + e.getMessage());
		}
	}

	public int insert(MemberVO mv) {
		int result = 0;

		try {
			conn = DriverManager.getConnection(url, dbId, dbPw);

			query = conn.prepareStatement("insert into member values (?, ?, ?, ?, to_date(?,'yyyy-mm-dd'))");
			query.setInt(1, mv.getId());
			query.setString(2, mv.getName());
			query.setString(3, mv.getEmail());
			query.setString(4, mv.getPassword());
			query.setString(5, mv.getRegdate());
			result = query.executeUpdate();

			query.close();
			conn.close();
		} catch (SQLException e) {
			System.err.println("Could not insert member. " + e);
		}
		return result;
	}

	public int delete(int id) {
		int result = 0;

		try {
			conn = DriverManager.getConnection(url, dbId, dbPw);

			query = conn.prepareStatement("delete from member where id = ?");
			query.setInt(1, id);
			result = query.executeUpdate();

			query.close();
			conn.close();
		} catch (SQLException e) {
			System.err.println("Could not delete member. " + e);
		}
		return result;
	}

	public int update(int id, String email, String pw) {
		int result = 0;

		try {
			conn = DriverManager.getConnection(url, dbId, dbPw);

			query = conn.prepareStatement("update member set email = ?, password = ? where id = ?");
			query.setString(1, email);
			query.setString(2, pw);
			query.setInt(3, id);
			result = query.executeUpdate();

			query.close();
			conn.close();
		} catch (SQLException e) {
			System.err.println("Could not update member. " + e);
		}
		return result;
	}

	public MemberVO getMemberById(int id) {
		ResultSet rset = null;
		MemberVO mv = null;

		try {
			conn = DriverManager.getConnection(url, dbId, dbPw);
			
			query = conn.prepareStatement("select * from member where id = ?");
			query.setInt(1, id);
			rset = query.executeQuery();

			while (rset.next()) {
				mv = new MemberVO(rset.getInt("id"), rset.getString("name"), rset.getString("email"),
						rset.getString("password"), rset.getString("regdate"));
			}

			query.close();
			conn.close();
		} catch (SQLException e) {
			System.err.println("Could not get member. " + e);
		}
		return mv;
	}

	public List<MemberVO> getAllMembers() {
		ResultSet rset = null;
		List<MemberVO> list = new LinkedList<MemberVO>();

		try {
			conn = DriverManager.getConnection(url, dbId, dbPw);
			
			stmt = conn.createStatement();
			rset = stmt.executeQuery("select * from member order by id");

			while (rset.next()) {
				list.add(new MemberVO(rset.getInt("id"), rset.getString("name"), rset.getString("email"),
						rset.getString("password"), rset.getString("regdate")));
			}

			stmt.close();
			conn.close();
		} catch (SQLException e) {
			System.err.println("Could not get members. " + e);
		}
		return list;
	}

}
