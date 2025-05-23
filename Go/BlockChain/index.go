package main

import (
	"bytes"
	"crypto/sha256"
	"fmt"
	"strconv"
	"time"
)

// Block Structure
type Block struct {
	Timestamp     int64
	Data          []byte
	PrevBlockHash []byte
	Hash          []byte
}

// Blockchain Structure
type Blockchain struct {
	blocks []*Block
}

// SHA-256 Method for siple hash creator
func (b *Block) SetHash() {
	//This converts the block's Timestamp (number) into a string, and then to a byte slice.
	timestamp := []byte(strconv.FormatInt(b.Timestamp, 10))
	//This joins the previous block hash, the block’s data, and the timestamp into one big byte slice. This will be used as the input for hashing.
	headers := bytes.Join([][]byte{b.PrevBlockHash, b.Data, timestamp}, []byte{})
	//This computes the SHA-256 hash of the joined data. sha256.Sum256 returns a [32]byte array.
	hash := sha256.Sum256(headers)
	//This converts the [32]byte array into a []byte slice and stores it in the Hash field of the block
	b.Hash = hash[:]
}

// Constructor-like function to create a new Block.
func NewBlock(data string, prevBlockHash []byte) *Block {
	block := &Block{time.Now().Unix(), []byte(data), prevBlockHash, []byte{}}
	block.SetHash()
	return block
}

// Method belongs to the Blockchain struct for adding a new block
func (bc *Blockchain) AddBlock(data string) {
	//Get the las block, create a new one with the prev hash and append to the chain
	prevBlock := bc.blocks[len(bc.blocks)-1]
	newBlock := NewBlock(data, prevBlock.Hash)
	bc.blocks = append(bc.blocks, newBlock)
}

// Create the first block of the Blockchain
func NewGenesisBlock() *Block {
	return NewBlock("Genesis Block", []byte{})
}

// Create a pointer to a new Blockchain with the Genesis as it's first block
func NewBlockchain() *Blockchain {
	return &Blockchain{[]*Block{NewGenesisBlock()}}
}

func main() {
	//Create the BlockChain
	bc := NewBlockchain()

	//Adding Blocks
	bc.AddBlock("Send 1 BTC to Ivan")
	bc.AddBlock("Send 2 more BTC to Ivan")

	for _, block := range bc.blocks {
		fmt.Printf("Prev. hash %x\n", block.PrevBlockHash)
		fmt.Printf("Data: %s\n", block.Data)
		fmt.Printf("Hash: %x\n", block.Hash)
		fmt.Println()
	}
}
