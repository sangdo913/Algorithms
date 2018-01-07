
import java.awt.Point;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class Solution {

	static int N, M;
	static int TimeTable[][];
	static data data[];
	static boolean visited[];
	static int start;
	static int maxsat;
	static ArrayList<Integer> trace;
	static ArrayList<Integer> hotellist;

	static int minHotel[];
	public static void main(String...msg) {
		Scanner sc = new Scanner(System.in);
		int TestCase = sc.nextInt();

		for (int T = 1; T <= TestCase; T++) {

			N = sc.nextInt();
			M = sc.nextInt();
			TimeTable = new int[N][N];
			data = new data[N];
			visited = new boolean[N];
			hotellist = new ArrayList<Integer>();
			start = -1;
			maxsat = 0;
			minHotel = new int[N];
			trace = new ArrayList<Integer>();
			for (int i = 0; i < N - 1; i++) {
				for (int j = i + 1; j < N; j++) {
					int time = sc.nextInt();
					TimeTable[i][j] = time;
					TimeTable[j][i] = time;
				}
			}

			for (int i = 0; i < N; i++) {
				char type = sc.next().charAt(0);
				if (type == 'A') {
					start = i;
				}
				if (type == 'P') {
					data[i] = new data(type, sc.nextInt(), sc.nextInt());
				}
				else {
					if (type == 'H') {
						hotellist.add(i);
					}
					data[i] = new data(type);
				}
			}
			for (int i = 0; i < N; i++) {
				setMinHotel(i);
			}

			getMaxSat(new boolean[N], new ArrayList<Integer>(), start, 0, 0, 1);

			System.out.print("#" + T + " " + maxsat + " ");
			for (int i = 0; i <trace.size(); i++)
				System.out.print(trace.get(i) + 1 + " ");
			System.out.println();
		}

	}
	public static void setMinHotel(int node) {
		minHotel[node] = 99999;
		for (int i : hotellist) {
			minHotel[node] = Math.min(minHotel[node], TimeTable[i][node]);
		}
	}
	public static int getMinHotel(int node) {
		return minHotel[node];
	}
	public static void getMaxSat(boolean visited[], ArrayList<Integer> visit, int current, int time, int sat, int day) {

		//1. �ð����� 9�ð� �̸����� �˻�
		//2. ȣ������, �������� üũ

		for (int node = 0; node < N; node++) {

			if (day != M && node == start)
				continue;
			//�湮�� ���ϰ��
			if (visited[node]) {
				if (data[node].type != 'H')
					continue;
			}
			if (time + TimeTable[current][node] + data[node].time > 540) //9�ð��� �Ѿ�� üũ
				continue;

			//���׿� ������
			if (data[node].type == 'A') {
				//�ⱹ ���̸�
				if (day == M) {
					//üũ
					if (maxsat < sat) {
						maxsat = sat;
						trace.clear();
						for (int i = 0; i <visit.size(); i++)
							trace.add(visit.get(i));
						trace.add(node);
					}
					continue;
				}
				else {
					//�ⱹ���� �ƴϸ� �� �ʿ� ����
					continue;
				}
			}

			//ȣ�ڿ� ������
			if (data[node].type == 'H') {
				//�ⱹ ���� �ƴҶ�
				if (day < M) {
					visit.add(node);
					visited[node] = true;
					getMaxSat(visited, visit, node, 0, sat, day + 1);
				}
				else {
					//�ⱹ���̸� �� �ʿ����
					continue;
				}
			}
			else if (data[node].type == 'P') { //�������� ���ƺ� ���
				if (day != M && time + TimeTable[current][node] + data[node].time + getMinHotel(node) > 540) //���� �湮���� �湮�ߴٰ��� ȣ�ڿ��� �� �� ���� ���
					continue;
				if (day == M && time + TimeTable[current][node] + data[node].time + TimeTable[node][start] > 540) //���� �湮���� �鷶�ٰ��� ���׿� �� �� ���� ���
					continue;
				visit.add(node);
				visited[node] = true;
				getMaxSat(visited, visit, node, time + TimeTable[current][node] + data[node].time, sat + data[node].sat, day);
			}
			visited[node] = false;
			visit.remove(visit.size() - 1);
		}



	}

}

class data {
	char type; //����
	int time = 0; //���ð�
	int sat = 0; //������
	public data(char t) {
		type = t;
	}
	public data(char t, int ti, int s) {
		type = t;
		time = ti;
		sat = s;
	}
}