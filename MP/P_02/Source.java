// Wydrzynski Krzysztof - 4
import java.util.Scanner;
public class Source{
	public static Scanner in = new Scanner(System.in);
	public static void main(String[]w){
		int n=in.nextInt(),o,z,j;
		for (int i=0;i<n;i++){
			z=1;
			int dss=in.nextInt();
			int[] ds=new int[dss];
			ds[0]=in.nextInt();
			for(j=1;j<dss;j++){
			    ds[j]=in.nextInt();
                if(ds[j-1]<ds[j])z++;
            }
			o=in.nextInt();
			for (j=0;j<o;j++){
				int f=in.nextInt(),s=in.nextInt(),l = 0;
				for(int k=f;k<=s;k++){
					int le=0,r=dss-1,ml,rs=0;
					while(le<r){
						ml=(le+r)/2;
						if (ds[ml]<k) {
							le=ml+1;} else {
							r=ml;}}
					if (ds[le]==k) {
						rs++;
						int tmp=le;
						while(tmp+1<dss&&ds[tmp+1]==k){
							tmp++;
							rs++;}
						tmp=le;
						while (tmp-1>=0&&ds[tmp-1]==k){
							tmp--;
							rs++;}}
					l += rs;}
				System.out.println(l);}
			System.out.println(z);}}}