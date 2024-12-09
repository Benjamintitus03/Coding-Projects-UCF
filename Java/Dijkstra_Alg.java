import java.io.*;
import java.util.*;

public class optionalproject {
    public static void main(String[] args) throws IOException {
        // Input and output file names
        String inputFileName = "cop3503-dijkstra-input.txt";
        String outputFileName = "cop3503-dijkstra-output-titus-benjamin.txt";

        // Read input from the file
        BufferedReader br = new BufferedReader(new FileReader(inputFileName));
        int vertices = Integer.parseInt(br.readLine().trim()); // Number of vertices
        int source = Integer.parseInt(br.readLine().trim()) - 1; // Source vertex (convert to 0-indexed)
        int edges = Integer.parseInt(br.readLine().trim()); // Number of edges

        // Adjacency list representation of the graph
        List<List<Edge>> graph = new ArrayList<>();
        for (int i = 0; i < vertices; i++) {
            graph.add(new ArrayList<>());
        }

        // Read edges
        for (int i = 0; i < edges; i++) {
            String[] edgeData = br.readLine().trim().split("\\s+");
            int u = Integer.parseInt(edgeData[0]) - 1; // 0-indexed vertex
            int v = Integer.parseInt(edgeData[1]) - 1; // 0-indexed vertex
            int weight = Integer.parseInt(edgeData[2]);
            // Add edge to the graph (doubly connected)
            graph.get(u).add(new Edge(v, weight));
            graph.get(v).add(new Edge(u, weight));
        }
        br.close();

        // Run Dijkstra's Algorithm
        int[] dist = new int[vertices];
        int[] prev = new int[vertices];
        dijkstra(graph, source, dist, prev);

        // Write output to file
        BufferedWriter bw = new BufferedWriter(new FileWriter(outputFileName));
        bw.write(vertices + "\n");
        for (int i = 0; i < vertices; i++) {
            bw.write((i + 1) + " " + (dist[i] == Integer.MAX_VALUE ? -1 : dist[i]) + " "
                    + (prev[i] == -1 ? -1 : (prev[i] + 1)) + "\n");
        }
        bw.close();
        System.out.println("Output written to " + outputFileName);
    }

    // Helper method to run Dijkstra's algorithm
    private static void dijkstra(List<List<Edge>> graph, int source, int[] dist, int[] prev) {
        int vertices = graph.size();
        Arrays.fill(dist, Integer.MAX_VALUE);
        Arrays.fill(prev, -1);

        // Min-heap to store (distance, vertex)
        PriorityQueue<Pair> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a.distance));
        dist[source] = 0;
        pq.add(new Pair(source, 0));

        while (!pq.isEmpty()) {
            Pair current = pq.poll();
            int u = current.vertex;

            // Iterate over neighbors of u
            for (Edge edge : graph.get(u)) {
                int v = edge.target;
                int weight = edge.weight;

                // Relaxation step
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    pq.add(new Pair(v, dist[v]));
                }
            }
        }
    }

    // Edge class to represent graph edges
    private static class Edge {
        int target, weight;

        Edge(int target, int weight) {
            this.target = target;
            this.weight = weight;
        }
    }

    // Pair class for priority queue
    private static class Pair {
        int vertex, distance;

        Pair(int vertex, int distance) {
            this.vertex = vertex;
            this.distance = distance;
        }
    }
}
