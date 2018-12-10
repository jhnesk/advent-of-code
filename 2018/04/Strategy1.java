import java.io.*;
import java.util.*;
import java.util.regex.*;
import java.util.stream.*;

public class Strategy1 {

	private final static int BEGIN = 0;
	private final static int SLEEP = 1;
	private final static int WAKE = 2;

	private final static Pattern guardPattern = Pattern.compile(".*#(\\d+).*");

	public static void main(String args[]) throws IOException {

		List<Event> notes = new ArrayList<>();

		File file = new File(args[0]);
		try (Scanner scanner = new Scanner(file)) {
			while (scanner.hasNextLine()) {
				scanner.skip("\\[");
				String date = scanner.next();
				String time = scanner.next();
				int hour = Integer.parseInt(time.substring(0,2));
				int minute = Integer.parseInt(time.substring(3,5));
				String note = scanner.nextLine();
				int eventType = getEventType(note);
				String guard = getGuard(note);
				notes.add(new Event(date, hour, minute, eventType, guard));
			}
		}
		Collections.sort(notes);

		Map<String, Integer[]> guardTimes = new HashMap<>();

		String guard = null;
		int sleep = 0;
		for (Event event : notes) {
			String nextGuard = event.guard;
			if (nextGuard != null) {
				guard = nextGuard;
			}
			Integer[] minutes = guardTimes.computeIfAbsent(guard, Strategy1::createArray);
			if (event.eventType == SLEEP) {
				sleep = event.minute;
			}
			if (event.eventType == WAKE) {
				for (int i = sleep; i < event.minute; i++) {
					minutes[i]++;
				}
			}
		}

		String maxGuard = "";
		int maxSum = 0;
		for (Map.Entry<String, Integer[]> guardTime : guardTimes.entrySet()) {
			int sum = sum(guardTime.getValue());
			if (sum > maxSum) {
				maxSum = sum;
				maxGuard = guardTime.getKey();
			}
		}
		Integer[] maxTimes = guardTimes.get(maxGuard);
		int bestMinute = getMostFrequentMinute(maxTimes);

		System.out.println("4.1: " + Integer.parseInt(maxGuard) * bestMinute);

		maxGuard = "";
		int maxMinute = 0;
		int maxIndex = 0;
		for (Map.Entry<String, Integer[]> guardTime : guardTimes.entrySet()) {
			int index = getMostFrequentMinute(guardTime.getValue());
			if (guardTime.getValue()[index] > maxMinute) {
				maxMinute = guardTime.getValue()[index];
				maxGuard = guardTime.getKey();
				maxIndex = index;
			}
		}
		System.out.println("4.2: " + Integer.parseInt(maxGuard) * maxIndex);
	}

	private static int getMostFrequentMinute(Integer[] minutes) {
		int bestMinute = 0;
		int bestValue = 0;
		for (int i = 0; i < 60; i++) {
			if (minutes[i] > bestValue) {
				bestValue = minutes[i];
				bestMinute = i;
			}
		}
		return bestMinute;
	}

	private static int sum(Integer[] values) {
		return Arrays.stream(values).mapToInt(i -> i.intValue()).sum();
	}

	private static Integer[] createArray(String key) {
		Integer[] array = new Integer[60];
		Arrays.fill(array, 0);
		return array;
	}

	private static int getEventType(String note) {
		if (note.contains("begins shift")) {
			return BEGIN;
		}
		if (note.contains("falls asleep")) {
			return SLEEP;
		}
		if (note.contains("wakes up")) {
			return WAKE;
		}
		throw new IllegalStateException("That's not a valid note! " + note);
	}

	private static String getGuard(String note) {
		Matcher matcher = guardPattern.matcher(note);
		if (matcher.matches()) {
			return matcher.group(1);
		}
		return null;
	}

	private static class Event implements Comparable<Event> {

		String date;
		int hour;
		int minute;
		String guard;
		int eventType;

		public Event(String date, int hour, int minute, int eventType, String guard) {
			this.date = date;
			this.hour = hour;
			this.minute = minute;
			this.eventType = eventType;
			this.guard = guard;
		}

		@Override
		public int compareTo(Event t) {
			if (!date.equals(t.date)) {
				return date.compareTo(t.date);
			}
			if (hour != t.hour) {
				return Integer.compare(hour, t.hour);
			}
			return Integer.compare(minute, t.minute);
		}
	}
}
