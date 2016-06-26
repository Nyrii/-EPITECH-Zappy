//
//  ViewController.swift
//  Zappy
//
//  Created by Kevin Empociello on 24/06/16.
//  Copyright © 2016 Kevin Empociello. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var responseText: UITextView!
    @IBOutlet weak var connectIndicator: UIView!
    @IBOutlet weak var indicatorView: UIActivityIndicatorView!
    @IBOutlet weak var portInput: UITextField!
    @IBOutlet weak var ipInput: UITextField!
    
    @IBOutlet weak var gaucheView: UIButton!
    @IBOutlet weak var prendreView: UIButton!
    @IBOutlet weak var avanceView: UIButton!
    @IBOutlet weak var poserView: UIButton!
    @IBOutlet weak var droiteView: UIButton!
    @IBOutlet weak var connectView: UIButton!
    @IBOutlet weak var lifeLabel: UILabel!
    
    var inventory = [0, 0, 0, 0, 0, 0, 0]
    var teamName = "Nekfeu"
    var isConnected = false
    var client: TCPClient!
    var timer : Timer!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.ipInput.text = "10.10.253.251"
        self.portInput.text = "8889"
        designMyView()
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        self.view.endEditing(true)
    }
    
    
    func designMyView() {
        indicatorView.isHidden = true;
        avanceView.layer.cornerRadius = 10
        gaucheView.layer.cornerRadius = 10
        droiteView.layer.cornerRadius = 10
        prendreView.layer.cornerRadius = 10
        poserView.layer.cornerRadius = 10
        connectView.layer.cornerRadius = 10
        connectIndicator.layer.cornerRadius = 10
        responseText.text = "disconnected"
    }
    
    func sendAction(msg: String) {
        let (success, errmsg) = client.send(str:"\(msg)\n")
        if success {
            readServer(type: "/\(msg)")
        } else {
            print(errmsg)
            responseText.text = errmsg
        }
    }
    
    func readServer(type: String) {
        var lastAnsw: String!;
        DispatchQueue.global(attributes: .qosUserInitiated).async {
            let data = self.client.read(expectlen: 1024*10)
            if let d = data {
                if let str = String(bytes: d, encoding: String.Encoding.utf8) {
                    lastAnsw = str
                    print(str)
                }
            }
            DispatchQueue.main.async {
                if (lastAnsw == nil) {
                    return ;
                }
                if (type == "/inventaire") {
                    if (lastAnsw == "ko") {
                        self.responseText.text = "ko"
                    } else {
                        self.updateInventoryData(data: lastAnsw)
                    }
                }
                else if (type == "/auth") {
                    if (lastAnsw == "ko") {
                        self.responseText.text = "ko"
                    } else {
                        self.responseText.text = "ready to play"
                        self.timer = Timer.scheduledTimer(timeInterval: 2, target: self, selector: "updateInventory", userInfo: nil, repeats: true)
                    }
                } else {
                    self.responseText.text = lastAnsw
                }
            }
        }
    }
    
    func updateInventoryData(data: String) {
        let arr = data.characters.split{$0 == " " || $0 == ","}.map(String.init)
        if (arr.count < 13) {
            return ;
        }
        var tmp = ""
        print(arr)
        self.inventory[0] = Int(arr[1])!
        self.inventory[1] = Int(arr[3])!
        self.inventory[2] = Int(arr[5])!
        self.inventory[3] = Int(arr[7])!
        self.inventory[4] = Int(arr[9])!
        self.inventory[5] = Int(arr[11])!
        for character in arr[13].characters {
            if (character >= "0" && character <= "9") {
                tmp.append(character)
            }
        }
        print("Tmp \(tmp)")
        self.inventory[6] = Int(tmp)!
        lifeLabel.text = "\(self.inventory[0])"
    }
    
    func updateInventory() {
        let (success, errmsg) = client.send(str:"inventaire\n")
        if success {
            readServer(type: "/inventaire")
        } else {
            print(errmsg)
            responseText.text = errmsg
        }
    }
    
    func disconnect() {
        connectIndicator.backgroundColor = UIColor.red()
        timer.invalidate()
        timer = nil
        connectView.setTitle("CONNECT", for: [])
        responseText.text = "disconnected"
        isConnected = false
        client = nil
        ipInput.isUserInteractionEnabled = true
        portInput.isUserInteractionEnabled = true
    }
    
    func updateState()
    {
        if (isConnected == true) {
            connectIndicator.backgroundColor = UIColor.green()
            connectView.setTitle("DISCONNECT", for: [])
        } else {
            connectIndicator.backgroundColor = UIColor.red()
        }
    }

    func authentificate() {
        let (success, errmsg) = client.send(str:"\(teamName)\n")
        if success {
            readServer(type: "/auth")
        } else {
            print(errmsg)
            responseText.text = errmsg
        }
    }
    
    @IBAction func connectBtn(sender: UIButton) {
        if (isConnected == true) {
            disconnect()
        } else {
        if (ipInput.text?.characters.count > 8 && portInput.text?.characters.count >= 2) {
            self.indicatorView.isHidden = false
            self.indicatorView.startAnimating()

            if let port = Int(portInput.text!){
                client = TCPClient(addr: ipInput.text!, port: port)
                let (success, errmsg) = client.connect(timeout: 1)
                if success {
                    print("connected !")
                    isConnected = true
                    responseText.text = "connected"
                    ipInput.isUserInteractionEnabled = false
                    portInput.isUserInteractionEnabled = false
                    updateState()
                    authentificate()
                } else {
                    print(errmsg)
                    responseText.text = errmsg
                    updateState()
                }
            
                self.indicatorView.stopAnimating()
                self.indicatorView.isHidden = true
            } else {
                responseText.text = "ko"
                updateState()
            }
        }
        }
    }
    
    @IBAction func avanceBtn(sender: UIButton) {
        if (isConnected == false || client == nil) {
            responseText.text = "you are disconnected"
            return ;
        }
        sendAction(msg: "avance");
    }
    
    @IBAction func droiteBtn(sender: UIButton) {
        if (isConnected == false || client == nil) {
            responseText.text = "you are disconnected"
            return ;
        }
        sendAction(msg: "droite");
    }
    
    @IBAction func gaucheBtn(sender: UIButton) {
        if (isConnected == false || client == nil) {
            responseText.text = "you are disconnected"
            return ;
        }
        sendAction(msg: "gauche");
    }
    
    @IBAction func prendreBtn(sender: UIButton) {
        if (isConnected == false || client == nil) {
            responseText.text = "you are disconnected"
            return ;
        }
        sendAction(msg: "prend nourriture"); // + object
    }
    
    @IBAction func poserBtn(sender: UIButton) {
        if (isConnected == false || client == nil) {
            responseText.text = "you are disconnected"
            return ;
        }
        sendAction(msg: "poser nourriture"); // + object
    }
    
    @IBAction func expulseBtn(sender: UIButton) {
        if (isConnected == false || client == nil) {
            responseText.text = "you are disconnected"
            return ;
        }
        sendAction(msg: "expulse");
    }
    
    @IBAction func forkBtn(sender: UIButton) {
        if (isConnected == false || client == nil) {
            responseText.text = "you are disconnected"
            return ;
        }
        sendAction(msg: "fork");
    }
    
    @IBAction func incantationBtn(sender: UIButton) {
        if (isConnected == false || client == nil) {
            responseText.text = "you are disconnected"
            return ;
        }
        sendAction(msg: "incantation");
    }
    
    @IBAction func broadcastBtn(sender: UIButton) {
        if (isConnected == false || client == nil) {
            responseText.text = "you are disconnected"
            return ;
        }
        sendAction(msg: "broadcast FEUUUUUU"); // + msg
    }
}

