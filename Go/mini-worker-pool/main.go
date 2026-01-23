package main

import (
	"fmt"
	"sync"
	"time"
)

func worker(id int, jobs <-chan int, wg *sync.WaitGroup, mu *sync.Mutex, total *int) {
	defer wg.Done()

	for job := range jobs {
		time.Sleep(100 * time.Millisecond)

		result := job * 2

		mu.Lock()
		*total += result
		mu.Unlock()

		fmt.Printf("Worker %d processed job %d -> %d\n", id, job, result)
	}
}

func main() {
	const numWorkers = 3
	const numJobs = 10

	var (
		wg sync.WaitGroup
		mu sync.Mutex
	)

	jobs := make(chan int)
	total := 0

	for i := 1; i <= numWorkers; i++ {
		wg.Add(1)
		go worker(i, jobs, &wg, &mu, &total)
	}

	for j := 1; j <= numJobs; j++ {
		jobs <- j
	}
	close(jobs)

	wg.Wait()

	fmt.Println("All jobs done.")
	fmt.Println("Total result: ", total)
}
