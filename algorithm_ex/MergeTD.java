
public class MergeTD extends AbstractSort {
	@SuppressWarnings("rawtypes")
	private static void merge(Comparable[] a, Comparable[] aux, int lo, int mid, int hi) {
		for (int k = lo; k <= hi; k++)
			aux[k] = a[k];

		int i = lo, j = mid + 1;
		for (int k = lo; k <= hi; k++) {
			if (i > mid)
				a[k] = aux[j++];
			else if (j > hi)
				a[k] = aux[i++];
			else if (less(aux[j], aux[i]))
				a[k] = aux[j++];
			else
				a[k] = aux[i++];
		}
	}
	@SuppressWarnings("rawtypes")
	public static void sort(Comparable[] a) {
		Comparable[] aux = new Comparable[a.length];
		sort(a,aux,0,a.length-1);
	}
	@SuppressWarnings("rawtypes")
	private static void sort(Comparable[] a, Comparable[] aux, int lo, int hi) {
		if(hi<=lo)
			return;
		int mid = lo + (hi-lo)/2;
		sort(a,aux, lo, mid);
		sort(a,aux,mid+1,hi);
		if(less(a[mid], a[mid+1]))
			return;
		merge(a,aux,lo,mid,hi);
	}

	public static void main(String[] args) {
		Integer[] a= {10,4,5,2,1,8,3,6};
		MergeTD.sort(a);
		MergeTD.show(a);
	}

}
