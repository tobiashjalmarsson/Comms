package lib

import (
	"errors"
	"math/big"
	"net"
	"net/rpc"
	"strings"
)

type RPCArgs struct {
	StringArg string
	BoolArg   bool
	IntArg    int
}

type RPCRes struct {
	StringResult string
	BoolResult   bool
}

// ChordRPC invokes method on the node of given address.
func (node *Node) ChordRPC(address string, methodName string, args *RPCArgs, res *RPCRes) error {
	if address != node.address {
		conn, err := net.Dial("tcp", address)
		if err != nil {
			if address == node.GetSuccessor() {
				for i := 1; i < len(node.successors); i++ {
					if node.successors[i] != node.address && node.successors[i] != address {
						node.SetSuccessor(node.successors[i])
						err := node.Notify(node.GetSuccessor())
						if err != nil {
							return err
						}
						return nil
					}
				}
				node.SetSuccessor(node.address)
				node.predecessor = ""
			} else if address == node.predecessor {
				node.predecessor = ""
				return nil
			}
			return err
		}
		client := rpc.NewClient(conn)
		defer client.Close()
		err = client.Call("Node."+methodName+"RPC", args, &res)
		return err
	} else {
		return errors.New(node.address + " calls its method " + methodName + " via RPC")
	}
}

func (node *Node) GetPredecessorRPC(_ *RPCArgs, res *RPCRes) error {
	res.StringResult = node.predecessor
	return nil
}

func (node *Node) GetSuccessorRPC(_ *RPCArgs, res *RPCRes) error {
	res.StringResult = node.GetSuccessor()
	return nil
}

func (node *Node) NotifiedRPC(args *RPCArgs, res *RPCRes) error {
	flag, err := node.Notified(args.StringArg)
	if err != nil {
		return err
	}
	res.BoolResult = flag
	return nil
}

func (node *Node) FindLocalSuccessorRPC(args *RPCArgs, res *RPCRes) error {
	var id *big.Int
	if !args.BoolArg {
		// args.stringArg is address, by default
		id = hash(args.StringArg)
	} else {
		// args.stringArg is ID
		id_, ok := new(big.Int).SetString(args.StringArg, 10)
		if !ok {
			return errors.New("SetString error")
		}
		id = id_
	}

	flag, successor := node.FindLocalSuccessor(id)
	res.StringResult = successor
	res.BoolResult = flag
	return nil
}

// SFTPDownloadFileRPC is the RPC version of SFTPDownloadFile.
// args.stringArg = "<address>;<file path>", args.boolArg = encrypted
func (node *Node) SFTPDownloadFileRPC(args *RPCArgs, _ *RPCRes) error {
	args_ := strings.Split(args.StringArg, ";")
	if len(args_) != 2 {
		return errors.New("invalid arguments")
	}
	address := args_[0]
	filePath := args_[1]
	err := node.SFTPDownloadFile(address, filePath, args.BoolArg)
	return err
}
