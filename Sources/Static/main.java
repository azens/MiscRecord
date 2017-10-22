import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.URLConnection;
import java.net.URL;

/*@src  http://eric-619.iteye.com/blog/693741*/
public class main
{
	public static void getHTML(String strURL) {
		String temp;
		try {
			URL url = new URL(strURL);
			URLConnection conn = url.openConnection();
			InputStreamReader isr = new InputStreamReader(conn.getInputStream());
			BufferedReader br = new BufferedReader(isr);
			while((temp = br.readLine()) != null) {
				System.out.println(temp);
			}
			br.close();
			isr.close();
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	public static void main(String[] args) {
		getHTML("http://www.baidu.com");
	}
}