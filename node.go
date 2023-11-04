package lib

import (
	"crypto/sha1"
	"fmt"
	"math/big"
)

func hash(address string) *big.Int {
	sha := sha1.New()
	sha.Write([]byte(address))
	return new(big.Int).SetBytes(sha.Sum(nil))
}

type Node struct {
	id         big.Int
	address    string
	neighbours []string
	successors []string
}

func NewNode(address string, numSuccessors int) *Node {
	return &Node{
		address:    address,
		id:         *hash(address),
		successors: make([]string, numSuccessors),
	}
}

func (node *Node) BuildSuccessors() error {

	target := node.GetSuccessor()
	node.successors[0] = target
	for i := 1; i < len(node.successors); i++ {
		if target != node.address {
			rpcArgs := &RPCArgs{}
			var rpcRes RPCRes
			err := node.ChordRPC(target, "GetSuccessor", rpcArgs, &rpcRes)
			if err != nil {
				return err
			}
			node.successors[i] = rpcRes.StringResult
			target = rpcRes.StringResult
		} else {
			node.successors[i] = target
		}
	}
	return nil
}

func (node *Node) SetSuccessor(successor string) {
	node.fingerTable[1] = successor
}

func (node *Node) GetSuccessor() string {
	return node.fingerTable[1]
}

func (node *Node) LookUp(filename string) (string, error) {
	fileId := hash(filename)
	successor := node.GetSuccessor()
	var resAddr string
	if between(&node.id, fileId, hash(successor), true) {
		resAddr = successor
	} else {
		rpcArgs := &RPCArgs{StringArg: fileId.String(), BoolArg: true}
		var rpcRes RPCRes
		err := node.FindSuccessor(rpcArgs, &rpcRes, successor)
		if err != nil {
			return "", err
		}
		resAddr = rpcRes.StringResult
	}
	return resAddr, nil
}

func (node *Node) PrintState(showTable bool) {
	node.Show()
	if showTable {
		node.ShowFingerTable()
	}
	node.ShowSuccessors()
}

func (node *Node) Show() {
	fmt.Sprintf("id: %0"+fmt.Sprintf("%d", M/4)+"x\n", &node.id)
	fmt.Println("address:", node.address)
	fmt.Println("predecessor:", node.predecessor)
	fmt.Println("successor:", node.GetSuccessor())
}

func (node *Node) ShowFingerTable() {
	for idx, val := range node.fingerTable {
		if idx == 0 {
			// Skip the first entry
			continue
		}
		fmt.Printf("[Index : %d] : [ Address : %s ]\n", idx, val)
	}
}

func (node *Node) ShowSuccessors() {
	fmt.Println("successors:")
	for idx, val := range node.successors {
		fmt.Printf("[Index : %d] : [ Address : %s ]\n", idx, val)
	}
}
