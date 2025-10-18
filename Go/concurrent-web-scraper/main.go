package main

import (
	"encoding/csv"
	"fmt"
	"github.com/gocolly/colly"
	"log"
	"os"
	"strconv"
	"sync"
)

type Product struct {
	URL   string
	Image string
	Name  string
	Price string
}

var (
	products  []Product
	mu        sync.Mutex
	wg        sync.WaitGroup
	selectors []string
)

func runScrapers(selector string, c *colly.Collector) {
	c.OnHTML(selector, func(e *colly.HTMLElement) {
		product := Product{}

		product.URL = e.ChildAttr("a", "href")
		product.Image = e.ChildAttr("img", "src")
		product.Price = e.ChildText(".price")
		product.Name = e.ChildText(".product-name")

		mu.Lock()
		products = append(products, product)
		mu.Unlock()
	})

	err := c.Visit("https://www.scrapingcourse.com/ecommerce")
	if err != nil {
		log.Fatalln("Failed to visit the website:", err)
	}
}

func main() {
	threads := 1

	if os.Args[1] != "" {
		threads, _ = strconv.Atoi(os.Args[1])
	}

	for i := range os.Args {
		if i == 1 || i == 0 {
			continue
		}

		selectors = append(selectors, os.Args[i])
	}

	for i := 0; i < threads; i++ {
		wg.Add(1)

		go func(id int) {
			defer wg.Done()

			for j := id - 1; j < len(selectors); j += threads {
				selector := selectors[j]
				fmt.Printf("[Thread %d] Started scraper for selector: %s\n", id, selector)

				c := colly.NewCollector(
					colly.AllowedDomains("www.scrapingcourse.com"),
				)

				runScrapers(selector, c)
			}
		}(i + 1)
	}

	wg.Wait()

	file, err := os.Create("products.csv")

	if err != nil {
		log.Fatalln("Failed to create output for CSV:", err)
	}

	defer func(file *os.File) {
		err := file.Close()
		if err != nil {
			log.Fatalln("Failed to close the file:", err)
		}
	}(file)

	writer := csv.NewWriter(file)

	headers := []string{
		"URL",
		"Image",
		"Name",
		"Price",
	}

	err = writer.Write(headers)
	if err != nil {
		log.Fatalln("Failed to write headers to CSV file:", err)
	}

	for _, product := range products {
		record := []string{
			product.URL,
			product.Image,
			product.Name,
			product.Price,
		}

		err = writer.Write(record)
		if err != nil {
			log.Fatalln("Failed to write record to CSV file:", err)
		}
	}

	defer writer.Flush()
}
